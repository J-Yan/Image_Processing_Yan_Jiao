# Volumetric Light Simulation
This project is a team project.

I mainly implemented the shader part.

## Main idea
We implemented two methods: radial blur and ray-tracing.

The final effect can be found at [backto1995.com/JIAO_YAN](https://backto1995.com/JIAO_YAN/), in section "OpenGL Volumetric Lighting Simulation".

###### Radial blur
- Capture the real time frame to frame buffer
- Change the current frame to gray image and hilight the bright part
- Apply radial blur to gray image with the light source location as the blur center to make the volumetric light effect
- merge the blurred image and the original image to get the final effect

###### Ray-tracing
- For each pixel in the screen, we create a line vertical to the screen
- Set a step length on this line, and for each step, decide whether this step point can be lighted by the light source, if yes, give it a bright value, if no, give it a dark value.
- Add all the step values together, and normalize it to the screen color range to form the final effect layer
- Finally, add the effect layer to the original screen
