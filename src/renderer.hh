#pragma once

#include "./glad/glad.h"
#include "./libs/tiny_gltf.h"
#include "./components/scene.hh"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// stdlib
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <atomic>
#include <unordered_map>

class Renderer {
public:
  bool m_should_shutdown = false;

  // Window control
  bool m_is_mouse_grabbed = true;
  bool m_is_mouse_on_cooldown = false;
  bool m_first_mouse = true;
  bool m_last_mouse_state = false;
  int m_viewport_width = 1920;
  int m_viewport_height = 1080;

  GLFWwindow* associated_window;
  
  // camera
  float m_camera_base_speed = 1.0f;
  glm::vec3 m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 m_cameraLookAt = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 m_direction = {0.0f, 0.0f, 0.0f};

  // Player Position 
  double m_lastX = 0;
  double m_lastY = 0;
  double m_yaw = 0;
  double m_pitch = 0;
  
  // bungie employees hate this one simple trick
  float m_deltaTime = 0.0f;
  float m_lastFrame = 0.0f;

  // Render properties
  float m_render_mode_wireframe = false;
  unsigned int window_depth_map;
  unsigned int window_depth_map_fbo;
  Shader* depth_shader;
  
  // Scene management
  Scene m_active_scene;
  std::atomic<uint32_t> num_loaded_textures = 0;

  std::vector<std::tuple<std::string, unsigned int, GLuint>> m_texture_map;

  /////////////////////
  // CALLBACK FUNCTIONS
  /////////////////////
  
  void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
  void mouse_callback(GLFWwindow *window, double xpos, double ypos);
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  void processInput(GLFWwindow *window);

  template <typename T> void upload_to_uniform(std::string location, GLuint shader_id, T input);

  void init_scene_vbos();
  void init_scene();
  void render_frame();

  /////////////////////
  // RENDER FUNCTIONS
  /////////////////////

  Renderer(uint window_width, uint window_height);
 
};

