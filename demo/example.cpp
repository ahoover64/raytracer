#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <gssmraytracer/geometry/Primitive.h>
#include "gssmraytracer/geometry/Sphere.h"
#include "gssmraytracer/geometry/Plane.h"

#include <gssmraytracer/utils/CmdLineFind.h>
#include <gssmraytracer/utils/Image.h>
#include <gssmraytracer/utils/RenderGlobals.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/Color.h>

#include "gssmraytracer/lights/Light.h"
#include "gssmraytracer/lights/PointLight.h"
#include "gssmraytracer/lights/DirectionLight.h"

#include "gssmraytracer/shaders/LambertianShader.h"
#include "gssmraytracer/shaders/CheckeredShader.h"
#include "gssmraytracer/shaders/RefShader.h"
#include <gssmraytracer/shaders/Shader.h>

#include <gssmraytracer/math/Vector.h>

#include <iostream>
#include <memory>
#include <omp.h>

using namespace gssmraytracer::utils;
using namespace gssmraytracer::geometry;
using namespace gssmraytracer::math;
using namespace gssmraytracer::shaders;
using namespace gssmraytracer::lights;

void display_picture() {
  const Image image = RenderGlobals::getInstance().getImage();
  const float *pixmap = image.getPixelBuffer();
  glClearColor(0 , 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(image.getWidth(), image.getHeight(), GL_RGBA, GL_FLOAT, (void *)pixmap);
  glFlush();


}

void handle_key(unsigned char key, int x, int y) {
   switch(key){
        case 'w':
        case 'W':
        //    writeimage();
            break;

        case 'r':
        case 'R':
      //      readImage();
      //      glutReshapeWindow(image.columns(), image.rows());
      //      glutPostRedisplay();
            break;

        case 'q':               // q - quit
        case 'Q':
        case 27:                // esc - quit
            exit(0);

        default:                // not a valid key -- just ignore it
            return;
    }


}

void checker(Image &image, const int num_squares, const Color color1, const Color color2) {

  int square_width = image.getWidth()/num_squares;
  for (int row = 0; row < image.getHeight(); ++row) {
    for (int col = 0; col < image.getWidth(); ++col) {
      if ((col/square_width + row/square_width) % 2 == 0) {
        image.setPixel(row, col, color1);
      }
      else {
        image.setPixel(row, col, color2);
      }

    }
  }
}

void stripes(Image &image, int num_stripes, Color color1, Color color2) {

  int stripe_width = image.getWidth()/num_stripes;
  for (int row = 0; row < image.getHeight(); ++row) {
    for (int col = 0; col < image.getWidth(); ++col) {
      if ((col/stripe_width) %2 == 0) {
        image.setPixel(row, col, color1);
      }
      else {
        image.setPixel(row, col, color2);
      }

    }
  }
}

void gradient(Image &image) {

  for (int row = 0; row < image.getHeight(); ++row) {
    for (int col = 0; col < image.getWidth(); ++col) {
      float normalized = (float)col/image.getWidth()/4.0;
        image.setPixel(row, col, Color(sin(normalized*2 * M_PI) * 1,1,0,1));
    }
  }
}

int main(int argc, char* argv[]) {
    // Use the default constructor
    CmdLineFind clf(argc, argv);

    int width = clf.find("-NX", 1280, "Image width");
    int height = clf.find("-NY", 720, "Image height");
    std::string filename = clf.find("-name", "demo.exr", "Name of output image file");

    clf.usage("-h");

    Image image(width, height);
    //Camera camera(Point(-5,0,-40),Vector(0,0,-1),Vector(0,1,0));

    Camera camera(Point(0,0,50),Vector(0,0,-1),Vector(0,1,0));
    camera.setAspectRatio((float) width / height);

    std::shared_ptr<Light> light(new PointLight(Color(1, 1, 1, 0), 250.f, Point(0, 15, 10)));
    Plane pl(Point(-5,0,10), Vector(1,1,0));
    Vector vec(-1,-1,0);
    //std::shared_ptr<Light> light(new DirectionLight(Color(1, 1, 1, 0), 5.f, pl, vec));

    Transform transform1, transform2;
    Vector position(-5.0,0.0,0.0);
    Vector position2(10.,-5.0,-5.0);
    transform1.translate(position);
    transform2.translate(position2);

    Scene &scene = Scene::getInstance();

    std::shared_ptr<Shader> shader(new LambertianShader(Color(0.f, 1.f, 0.f, 1.f)));
    std::shared_ptr<Shader> shader2(new RefShader(Color(0.f, .5f, .5f, 1.f), 5, 5.f, 5.f, 1.f, .5f));
    std::shared_ptr<Sphere> sphere(new Sphere(transform1, 5.0f));
    std::shared_ptr<Sphere> sphere2(new Sphere(transform2, 7.5f));

    std::shared_ptr<Shader> shader3(new CheckeredShader());
    std::shared_ptr<Plane> plane(new Plane(Vector(0.f,-15.f,0.f), Vector(0.f,1.f,0.f)));

    //Make the prmatives
    std::shared_ptr<Primitive> prim1(new Primitive(sphere, shader));
    std::shared_ptr<Primitive> prim2(new Primitive(sphere2, shader2));
    std::shared_ptr<Primitive> prim3(new Primitive(plane, shader3));


    scene.addPrimitive(prim1);
    scene.addPrimitive(prim2);
    scene.addPrimitive(prim3);
    scene.addLight(light);

    const int samp_size = 1; // SET NUMBER OF SAMPLES PER PIXEL

    set_num_threads(8);
    #pragma omp parallel for
    for(int r = 0; r < image.getHeight(); ++r) {
	    for(int c = 0; c < image.getWidth(); ++c) {
        Color color(0,0,0,1);
        for(int samp = 0; samp < samp_size; ++samp) {
           float epsilon = ((float) rand() / (RAND_MAX));
           float delta = ((float) rand() / (RAND_MAX));
    	     Ray ray(camera.eye(), camera.view((float) (c + epsilon) / image.getWidth(),
                                             (float) (r + delta) / image.getHeight()));
    	     std::shared_ptr<Primitive> p;
    	     float t;
    	     std::shared_ptr<DifferentialGeometry> dg;

    	     if(scene.hit(ray, t, dg, p)) {
    		       color = color + p->shade(dg, 0);
    	     }
    	     else {
    		       color = color + Color(1, 1, 1, 1);
    	     }
        }
        //std::cout << color.red << ", " << color.green << ", " << color.blue << ", " << color.alpha << std::endl;
        image.setPixel(r, c, color / (float) samp_size);
      }
	  }

    RenderGlobals::getInstance().setImage(image);

    //Image image3 = RenderGlobals::getInstance().getImage();
    image.write("test.png");


    // start up the glut utilities
    glutInit(&argc, argv);

    // create the graphics window, giving width, height, and title text
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);


    glutInitWindowSize(width, height);

    glutCreateWindow("Image");

    glutDisplayFunc(display_picture);

    glutKeyboardFunc(handle_key);

    glutMainLoop();


    return 0;

}
