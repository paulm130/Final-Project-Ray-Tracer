# Ray Tracer
This is a ray tracer that can generate photorealistic images. It uses OpenGL as the graphics API and GLUT for keyboard input. It has anti-aliasing and soft shadows. It supports mirror, diffuse, and matte-glossy materials. It supports importing custom scenes to then be rendered in the ray tracer. The ray tracer was developed for Windows but might also work on Linux or MacOS. \
I used the starter code from [CSE167 WI26 RayTracer Setup](https://cseweb.ucsd.edu/~alchern/teaching/cse167_wi26/RayTracer-init_setup.zip) and used [CSE167 WI26 Final Project](https://cseweb.ucsd.edu/~alchern/teaching/cse167_wi26/final-project.pdf) as guidance for creating the ray tracer.
## Instructions
1. From the root directory of the project open up a terminal and run `cd RayTracer-init_setup` then run `cd RayTracer-init_setup` again
2. Run `.\build.ps1` to run Windows build commands. This will not work on Linux or MacOS
3. Then run `.\build-win\bin\Release\RayTracer.exe a b c` 
   * replace a with spp
   * replace b with max ray bounces
   * replace c with scene selection and look in terminal for scene IDs
   * an example is run `.\build-win\bin\Release\RayTracer.exe 10 3 1` which will run the program with rendering setting of 10 spp and a maximum of 3 ray bounces. It will load in the file associated with scene ID 1 which is the Cornell box
4. After running the command it lists the controls and scene IDs. Here is an image of the instructions listed out in the terminal: [ray tracer instructions](/submission-images/ray-tracer-instructions.png)
## Customization
* The default is 25% diffuse lighting and 75% specular lighting for the matte-glossy material which makes the material look very shiny. This can be edited by changing the floating point values on line 132 of [MatteGlossyMaterial.cpp](/RayTracer-init_setup/RayTracer-init_setup/src/materials/MatteGlossyMaterial.cpp)
* To add in a custom scene:
  1. Create the custom scene. The custom scene must be a .inl file following a similar format to the other scenes. The other scenes are located in the [scenes directory](/RayTracer-init_setup/RayTracer-init_setup/src/scenes)
  2. Below line 23 in [RayTracer.cpp](/RayTracer-init_setup/RayTracer-init_setup/src/RayTracer.cpp) add in `#include "<file_path>"`
  3. Below line 100 in [RayTracer.cpp](/RayTracer-init_setup/RayTracer-init_setup/src/RayTracer.cpp) add in the code
   ```
   else if (scene_id == 6)
        scene = std::unique_ptr<Scene>(<your_scene>);
   ```
  4. To make it more clear below line 85 can add your scene ID to print statement in [main.cpp](RayTracer-init_setup/RayTracer-init_setup/main.cpp)
  5. To make error message more clear can change print statement on line 102 of [RayTracer.cpp](/RayTracer-init_setup/RayTracer-init_setup/src/RayTracer.cpp) from `" given (expected 1..5)"` to `" given (expected 1..<current_number_of_scenes>)"`
  6. Repeat all steps for each new custom scene you want to add in
## More
* If on Linux or MacOS can find build instructions in [BUILD.md](/RayTracer-init_setup/RayTracer-init_setup/BUILD.md)