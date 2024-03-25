# GraphGL
The project allows you to draw graphs. It uses the [GraphLib](https://github.com/yagginov/GraphLib) graph representation library.

For correct operation, you must first configure project dependencies:
  - [GLEW](https://glew.sourceforge.net/)
  - [GLFW](https://www.glfw.org/)
  - [FreeType](https://freetype.org/)
  - [glm](https://github.com/g-truc/glm)
  - [GraphLib](https://github.com/yagginov/GraphLib)

Also, stb_image_write is used to save the graph you have drawn as a photo, but it is not necessary to configure it additionally, since the required file is already included in the project. [stb](https://github.com/nothings/stb/blob/master/stb_image_write.h)

Management:
  - To be able to draw vertices, you need to press ***1*** on the keyboard, and then you can draw graph vertices with a mouse click. Numbering of vertices is automatic and it is impossible to change the name of the vertex (at least for now).
  - To specify edges between graph vertices, first press ***2*** on the keyboard. Then you need to select two vertices with mouse clicks and draw an edge between them (the edge is automatically considered bidirectional and has a base length of 1.0).
  - If you press ***3*** on the keyboard, you will get the opportunity to move both individual vertices of the graph, and several at once by selecting them.
  - To save the image of the graph, select all the vertices you want to save and press the combination CTRL + S. The image will be saved in the testfiles folder in .png format with transparency.
  - It is also possible to save the graph in a special formatted file, so that later when the program is loaded, it can be opened and not drawn from scratch.
