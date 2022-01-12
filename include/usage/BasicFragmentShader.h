#include <string>
#include <cmath>

#include "shaders/FragmentShader.h"
#include "math/math.h"

class BasicFragmentShader: public FragmentShader {
public:
  BasicFragmentShader(): FragmentShader {} {
    // TODO: remove? 
    inputBufferMap[0] = 4; // pos 
    inputBufferMap[1] = 2; // uvs
    inputBufferMap[2] = 3; // normal
    inputBufferMap[3] = 3; // lightPosition

    outputBufferMap[0] = 3; // screenCoord
    outputBufferMap[1] = 3; // colour 
  }

  ~BasicFragmentShader() = default;

  void run(GraphicsObject* fragmentIn, GraphicsObject* fragmentOut) {
    std::string shades = ".o*";

    // in
    vec4 pos; 
    vec2 uvs; 
    vec3 normal;
    vec3 lightPosition;

    // out
    vec3 screenCoord; 
    vec3 colour; 

    fragmentIn->get(0, pos);
    fragmentIn->get(1, uvs);
    fragmentIn->get(2, normal);
    fragmentIn->get(3, lightPosition);

    // because raterization interpolated the floats 
    normal.normalize();
    lightPosition.normalize();

    screenCoord = vec3(pos.x, pos.y, pos.z);

    float brightness = std::min(0.99f, vec3::dot(normal, lightPosition));
    int lightLevel = (int) std::floor(brightness * lightLevels.size() / 2);

    colour = vec3((int) (uvs.x * 8.0f) % 8, 100, lightLevel);

    fragmentOut->set(0, screenCoord);
    fragmentOut->set(1, colour);
  }

private:
  std::string lightLevels = "@#%&*=+o;~,.";
};
