
#include "calculator.c"

/**
 * Draws everything
 */

static void
_DRAW(void)
{

  const static GLfloat green[4] = {0.0, 1.0, 0.0, 1.0};
  const static GLfloat blue[4] = {0.2, 0.2, 1.0, 1.0};

  GLfloat transform[16];
  identity(transform);

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Translate and rotate the view */
  // x  ,  z,
  translate(transform, 0, 0, -20);
  // rotate(transform, 2 * M_PI * nidzaView_rot[0] / 360.0, 1, 0, 0);
  // rotate(transform, 2 * M_PI * nidzaView_rot[1] / 360.0, 0, 1, 0);
  // rotate(transform, 2 * M_PI * nidzaView_rot[2] / 360.0, 0, 0, 1);
  /* Draw the gears */
  //                                      x    y   angle      color

  // nidza_gear1 = nidza_create_gear(0.3, 1.0, 1.0, 15, 1);

  float step = 2 * PI / 20; // see note 1
  float h = 0;
  float k = -1; // + getMyX();
  float r = 5 + getMyX();
  float angleDir = -1;

  for (float theta = 0; theta < 2 * PI; theta += step)
  {
    angleDir = angleDir * -1;
    float x = h + r * cos(theta);
    float y = k - r * sin(theta);
    nidza_draw_gear(nidza_gear1, transform, x, y, angleDir * nidzaAngle, nidza_red);
  }

    // translate(transform, 0, 0, 0);
    //                      z , x, y
    // translate(transform, -2, 3, -10);
    draw_gear(gear1, transform, -0.0, -1.0, angle, blue);

    glutSwapBuffers();

}
