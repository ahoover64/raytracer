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
#include <sstream>
#include <memory>
#ifdef __OPENMP
#include <omp.h>
#endif

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

  Camera camera(Point(0,0,50),Vector(0,0,-1),Vector(0,1,0));
  camera.setAspectRatio((float) width / height);

  std::shared_ptr<Light> light(new PointLight(Color(1, 1, 1, 0), 100.f, Point(0, 20, 15)));
  //std::shared_ptr<Light> light(new DirectionLight(Color(1, 1, 1, 0), 5.f, pl, vec));

  Transform transform1, transform2, transform3, transform4, transform5;

  Vector position(-10.0,0.0,5.0);
  Vector position2(10.,2.5,5.0);
  Vector position3(0.f,7.5,-5.f);
  Vector position4(0.0,-2.5,0.0);
  Vector position5(0.f,-12.5,0.f);

  transform1.translate(position);
  transform2.translate(position2);
  transform3.translate(position3);
  transform4.translate(position4);
  transform5.translate(position5);

  Scene &scene = Scene::getInstance();
  scene.init();

  int MAX_BOUNCE = 5;

  std::shared_ptr<Shader> shader(new RefShader(Color(0.f, 1.f, 0.f, 1.f), MAX_BOUNCE, 1.f, .5f, 0.f, .5f));
  std::shared_ptr<Shader> shader2(new RefShader(Color(0.f, .5f, .5f, 1.f), MAX_BOUNCE, 1.f, .3f, 0.f, .5f));
  std::shared_ptr<Shader> shader3(new RefShader(Color(1.f, 0.f, 0.f, 1.f), MAX_BOUNCE, 1.f, .2f, 0.f, .5f));
  std::shared_ptr<Shader> shader4(new RefShader(Color(1.f, .5f, 0.f, 1.f), MAX_BOUNCE, 1.f, .5f, 0.f, .5f));

  std::shared_ptr<Sphere> sphere(new Sphere(transform1, 5.0f));
  std::shared_ptr<Sphere> sphere2(new Sphere(transform2, 6.f));
  std::shared_ptr<Sphere> sphere3(new Sphere(transform3, 5.0f));
  std::shared_ptr<Sphere> sphere4(new Sphere(transform4, 2.5f));

  std::shared_ptr<Shader> shader5(new CheckeredShader(Color(0.f,0.f,0.f,1.f), Color(1.f,1.f,1.f,1.f), 60.f));
  //std::shared_ptr<Plane> plane(new Plane(transform5, Vector(0.5f,0.f,.5f), Vector(.5f,0.f,-.5f)));

  //Make the prmatives
  std::shared_ptr<Primitive> prim1(new Primitive(sphere, shader));
  std::shared_ptr<Primitive> prim2(new Primitive(sphere2, shader2));
  std::shared_ptr<Primitive> prim3(new Primitive(sphere3, shader3));
  std::shared_ptr<Primitive> prim4(new Primitive(sphere4, shader4));
  //std::shared_ptr<Primitive> prim5(new Primitive(plane, shader5));


  scene.addPrimitive(prim1);
  scene.addPrimitive(prim2);
  scene.addPrimitive(prim3);
  scene.addPrimitive(prim4);
  //scene.addPrimitive(prim5);
  scene.addLight(light);

  const int samp_size = 1; // SET NUMBER OF SAMPLES PER PIXEL
  float x, z, theta;

  //omp_set_num_threads(4);
  #pragma omp parallel for
  for(int iter = 0; iter < 200; iter++) {
    //Create a new Camera
    theta = iter * 3.14159265358979 / 100.f;
    z = 50*cos(theta);
    x = 50*sin(theta);
    camera = Camera(Point(x,0,z),Vector(0,-1*sin(theta),-1*cos(theta)),Vector(0,1,0));
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
            color = color + Color(0,0,0,1);
          }
        }
        image.setPixel(r, c, color / (float) samp_size);
      }
    }

    //RenderGlobals::getInstance().setImage(image);
    std::stringstream ss;
    if(iter < 10) {ss << "images/ahoover15.000" << iter << ".exr";}
      else if(iter < 100) {ss << "images/ahoover15.00" << iter << ".exr";}
      else if(iter < 1000) {ss << "images/ahoover15.0" << iter << ".exr";}
      else {ss << "images/ahoover15." << iter << ".exr";}
      image.write(ss.str().c_str());
      std::cout << ss.str().c_str() << " " << " Done" << std::endl;
    }


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
