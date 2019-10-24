
/** The current gear rotation angle */
static GLfloat nidzaAngle = 0.0;

/** The view rotation [x, y, z] */
static GLfloat nidzaView_rot[3] = {0.0, 0.0, 0.0};

GLfloat nidza_red[4] = {0.0, 1.0, 0.0, 1.0};
double nidza_changeRedco = 0.0001;

/**
 * Struct describing the vertices in triangle strip
 */
struct nidza_vertex_strip
{
  /** The first vertex in the strip */
  GLint first;
  /** The number of consecutive vertices in the strip after the first */
  GLint count;
};

/* Each vertex consist of GEAR_VERTEX_STRIDE GLfloat attributes */
typedef GLfloat NidzaGearVertex[GEAR_VERTEX_STRIDE];

/**
 * Struct representing a gear.
 */
struct nidza_gear
{
  /** The array of vertices comprising the gear */
  NidzaGearVertex *vertices;
  /** The number of vertices comprising the gear */
  int nvertices;
  /** The array of triangle strips comprising the gear */
  struct nidza_vertex_strip *strips;
  /** The number of triangle strips comprising the gear */
  int nstrips;
  /** The Vertex Buffer Object holding the vertices in the graphics card */
  GLuint vbo;
};

/**
 * Fills a gear vertex.
 *
 * @param v the vertex to fill
 * @param x the x coordinate
 * @param y the y coordinate
 * @param z the z coortinate
 * @param n pointer to the normal table
 *
 * @return the operation error code
 */
static NidzaGearVertex *
nidza_vert(NidzaGearVertex *v, GLfloat x, GLfloat y, GLfloat z, GLfloat n[3])
{
  v[0][0] = x;
  v[0][1] = y;
  v[0][2] = z;
  v[0][3] = n[0];
  v[0][4] = n[1];
  v[0][5] = n[2];

  return v + 1;

  /*
  // ori
    v[0][0] = x;
  v[0][1] = y;
  v[0][2] = z;
  v[0][3] = n[0];
  v[0][4] = n[1];
  v[0][5] = n[2];
  */
}

static void
nidza_gears_idle(void)
{
  static int frames = 0;
  static double tRot0 = -1.0, tRate0 = -1.0;
  double dt, t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

  if (tRot0 < 0.0)
    tRot0 = t;
  dt = t - tRot0;
  tRot0 = t;


  /* advance rotation for next frame */
  nidzaAngle += 70.0 * dt; /* 70 degrees per second */
  if (nidzaAngle > 3600.0)
    nidzaAngle -= 3600.0;

  //-------------------------------
  if (nidza_red[2] > 1)
  {
    nidza_red[2] = 0;
  }

  if (nidza_red[1] > 1)
  {
    nidza_red[1] = 0;
  }

  if (nidza_red[0] > 1)
  {
    nidza_red[0] = 0;
  }

 // nidza_red[0] += nidza_changeRedco;
 //  nidza_red[1] += nidza_changeRedco;
 // nidza_red[2] += nidza_changeRedco;

  //////////////////////////////////////////

  glutPostRedisplay();
  frames++;

  if (tRate0 < 0.0)
    tRate0 = t;
  if (t - tRate0 >= 5.0)
  {
    GLfloat seconds = t - tRate0;
    GLfloat fps = frames / seconds;
    printf("%d frames in %3.1f seconds = %6.3f FPS\n", frames, seconds,
           fps);
    tRate0 = t;
    frames = 0;
  }
}

/**
 *  Create a gear wheel.
 *
 *  @param inner_radius radius of hole at center
 *  @param outer_radius radius at center of teeth
 *  @param width width of gear
 *  @param teeth number of teeth
 *  @param tooth_depth depth of tooth
 *
 *  @return pointer to the constructed struct gear
 */
static struct nidza_gear *
nidza_create_gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width,
                  GLint teeth, GLfloat tooth_depth)
{
  GLfloat r0, r1, r2;
  GLfloat da;
  NidzaGearVertex *v;
  struct nidza_gear *gear;
  double s[5], c[5];
  GLfloat normal[3];
  int cur_strip = 0;
  int i;

  /* Allocate memory for the gear */
  gear = malloc(sizeof *gear);
  if (gear == NULL)
    return NULL;

  /* Calculate the radii used in the gear */
  r0 = inner_radius;
  r1 = outer_radius - tooth_depth / 2;
  r2 = outer_radius + tooth_depth / 2;

  da = 2.0 * M_PI / teeth / 4.0;

  /* Allocate memory for the triangle strip information */
  gear->nstrips = STRIPS_PER_TOOTH * teeth;
  gear->strips = calloc(gear->nstrips, sizeof(*gear->strips));

  /* Allocate memory for the vertices */
  gear->vertices = calloc(VERTICES_PER_TOOTH * teeth, sizeof(*gear->vertices));
  v = gear->vertices;

  for (i = 0; i < teeth; i++)
  {
    /* Calculate needed sin/cos for varius angles */
    sincos(i * 2.0 * M_PI / teeth, &s[0], &c[0]);
    sincos(i * 2.0 * M_PI / teeth + da, &s[1], &c[1]);
    sincos(i * 2.0 * M_PI / teeth + da * 2, &s[2], &c[2]);
    sincos(i * 2.0 * M_PI / teeth + da * 3, &s[3], &c[3]);
    sincos(i * 2.0 * M_PI / teeth + da * 4, &s[4], &c[4]);

    /* A set of macros for making the creation of the gears easier */
#define GEAR_POINT(r, da)      \
  {                            \
    (r) * c[(da)], (r)*s[(da)] \
  }
#define SET_NORMAL(x, y, z) \
  do                        \
  {                         \
    normal[0] = (x);        \
    normal[1] = (y);        \
    normal[2] = (z);        \
  } while (0)
//                                                                                                 depth exclude 0.5
#define NIDZA_GEAR_VERT(v, point, sign) nidza_vert((v), p[(point)].x, p[(point)].y, (sign)*width * 0.5, normal)

#define START_STRIP                                     \
  do                                                    \
  {                                                     \
    gear->strips[cur_strip].first = v - gear->vertices; \
  } while (0);

#define END_STRIP                                                         \
  do                                                                      \
  {                                                                       \
    int _tmp = (v - gear->vertices);                                      \
    gear->strips[cur_strip].count = _tmp - gear->strips[cur_strip].first; \
    cur_strip++;                                                          \
  } while (0)

#define NIDZA_QUAD_WITH_NORMAL(p1, p2)                                      \
  do                                                                  \
  {                                                                   \
    SET_NORMAL((p[(p1)].y - p[(p2)].y), -(p[(p1)].x - p[(p2)].x), 0); \
    v = NIDZA_GEAR_VERT(v, (p1), -1);                                       \
    v = NIDZA_GEAR_VERT(v, (p1), 1);                                        \
    v = NIDZA_GEAR_VERT(v, (p2), -1);                                       \
    v = NIDZA_GEAR_VERT(v, (p2), 1);                                        \
  } while (0)

    struct point
    {
      GLfloat x;
      GLfloat y;
    };

    /* Create the 7 points (only x,y coords) used to draw a tooth */
    struct point p[7] = {
        GEAR_POINT(r2, 1), // 0
        GEAR_POINT(r2, 2), // 1
        GEAR_POINT(r1, 0), // 2
        GEAR_POINT(r1, 3), // 3
        GEAR_POINT(r0, 0), // 4
        GEAR_POINT(r1, 4), // 5
        GEAR_POINT(r0, 4), // 6
    };

    /* Front face */
    START_STRIP;
    SET_NORMAL(0, 0, 1.0);
    v = NIDZA_GEAR_VERT(v, 0, +1);
    v = NIDZA_GEAR_VERT(v, 1, +1);
    v = NIDZA_GEAR_VERT(v, 2, +1);
    v = NIDZA_GEAR_VERT(v, 3, +1);
    v = NIDZA_GEAR_VERT(v, 4, +1);
    v = NIDZA_GEAR_VERT(v, 5, +1);
    v = NIDZA_GEAR_VERT(v, 6, +1);
    END_STRIP;

    /* Inner face */
    START_STRIP;
    NIDZA_QUAD_WITH_NORMAL(4, 6);
    END_STRIP;

    /* Back face */
    START_STRIP;
    SET_NORMAL(0, 0, -1.0);
    v = NIDZA_GEAR_VERT(v, 6, -1);
    v = NIDZA_GEAR_VERT(v, 5, -1);
    v = NIDZA_GEAR_VERT(v, 4, -1);
    v = NIDZA_GEAR_VERT(v, 3, -1);
    v = NIDZA_GEAR_VERT(v, 2, -1);
    v = NIDZA_GEAR_VERT(v, 1, -1);
    v = NIDZA_GEAR_VERT(v, 0, -1);
    END_STRIP;

    /* Outer face */
    START_STRIP;
    NIDZA_QUAD_WITH_NORMAL(0, 2);
    END_STRIP;

    START_STRIP;
    NIDZA_QUAD_WITH_NORMAL(1, 0);
    END_STRIP;

    START_STRIP;
    NIDZA_QUAD_WITH_NORMAL(3, 1);
    END_STRIP;

    START_STRIP;
    NIDZA_QUAD_WITH_NORMAL(5, 3);
    END_STRIP;
  }

  gear->nvertices = (v - gear->vertices);

  /* Store the vertices in a vertex buffer object (VBO) */
  glGenBuffers(1, &gear->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, gear->vbo);
  glBufferData(GL_ARRAY_BUFFER, gear->nvertices * sizeof(NidzaGearVertex),
               gear->vertices, GL_STATIC_DRAW);

  return gear;
}


// #include "gl-program.c"

// --


/**
 * Draws a gear.
 *
 * @param gear the gear to draw
 * @param transform the current transformation matrix
 * @param x the x position to draw the gear at
 * @param y the y position to draw the gear at
 * @param angle the rotation angle of the gear
 * @param color the color of the gear
 */
static void
nidza_draw_gear(struct nidza_gear *gear, GLfloat *transform,
                GLfloat x, GLfloat y, GLfloat angle, const GLfloat color[4])
{

  /**
   * update idle here
   * */

  nidza_gears_idle();

  GLfloat model_view[16];
  GLfloat normal_matrix[16];
  GLfloat model_view_projection[16];

  /* Translate and rotate the gear */
  memcpy(model_view, transform, sizeof(model_view));
  translate(model_view, x, y, 0);
  rotate(model_view, 2 * M_PI * angle / 360.0, 0, 0, 1);

  /* Create and set the ModelViewProjectionMatrix */
  memcpy(model_view_projection, ProjectionMatrix, sizeof(model_view_projection));
  multiply(model_view_projection, model_view);

  glUniformMatrix4fv(ModelViewProjectionMatrix_location, 1, GL_FALSE,
                     model_view_projection);

  /*
    * Create and set the NormalMatrix. It's the inverse transpose of the
    * ModelView matrix.
    */
  memcpy(normal_matrix, model_view, sizeof(normal_matrix));
  invert(normal_matrix);
  transpose(normal_matrix);
  glUniformMatrix4fv(NormalMatrix_location, 1, GL_FALSE, normal_matrix);

  /* Set the gear color */
  glUniform4fv(MaterialColor_location, 1, color);

  /* Set the vertex buffer object to use */
  glBindBuffer(GL_ARRAY_BUFFER, gear->vbo);

  /* Set up the position of the attributes in the vertex buffer object */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), NULL);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        6 * sizeof(GLfloat), (GLfloat *)0 + 3);

  /* Enable the attributes */
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  /* Draw the triangle strips that comprise the gear */
  int n;
  for (n = 0; n < gear->nstrips; n++)
    glDrawArrays(GL_TRIANGLE_STRIP, gear->strips[n].first, gear->strips[n].count);
    // glDrawArrays(GL_TRIANGLE_STRIP, gear->strips[n].first, gear->strips[n].count);

  /* Disable the attributes */
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);
}



/**
 * Handles a new window size or exposure.
 *
 * @param width the window width
 * @param height the window height
 */
static void
nidza_gears_reshape(int width, int height)
{
  /* Update the projection matrix */
  perspective(ProjectionMatrix, 60.0, width / (float)height, 1.0, 1024.0);

  /* Set the viewport */
  glViewport(0, 0, (GLint)width, (GLint)height);
}

/**
 * Handles special glut events.
 *
 * @param special the event to handle.
 */
static void
nidza_gears_special(int special, int crap, int morecrap)
{

  printf("test mouse event");
  switch (special)
  {
  case GLUT_KEY_LEFT:
    view_rot[1] += 5.0;
    break;
  case GLUT_KEY_RIGHT:
    view_rot[1] -= 5.0;
    break;
  case GLUT_KEY_UP:
    view_rot[0] += 5.0;
    break;
  case GLUT_KEY_DOWN:
    view_rot[0] -= 5.0;
    break;
  }
}

static void
nidza_gears_init(void)
{
  GLuint v, f, program;
  const char *p;
  char msg[512];

  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  /* Compile the vertex shader */
  p = vertex_shader;
  v = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(v, 1, &p, NULL);
  glCompileShader(v);
  glGetShaderInfoLog(v, sizeof msg, NULL, msg);
  printf("vertex shader info: %s\n", msg);

  /* Compile the fragment shader */
  p = fragment_shader;
  f = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(f, 1, &p, NULL);
  glCompileShader(f);
  glGetShaderInfoLog(f, sizeof msg, NULL, msg);
  printf("fragment shader info: %s\n", msg);

  /* Create and link the shader program */
  program = glCreateProgram();
  glAttachShader(program, v);
  glAttachShader(program, f);
  glBindAttribLocation(program, 0, "position");
  glBindAttribLocation(program, 1, "normal");

  glLinkProgram(program);
  glGetProgramInfoLog(program, sizeof msg, NULL, msg);
  printf("info: %s\n", msg);

  /* Enable the shaders */
  glUseProgram(program);

  /* Get the locations of the uniforms so we can access them */
  ModelViewProjectionMatrix_location = glGetUniformLocation(program, "ModelViewProjectionMatrix");
  NormalMatrix_location = glGetUniformLocation(program, "NormalMatrix");
  LightSourcePosition_location = glGetUniformLocation(program, "LightSourcePosition");
  MaterialColor_location = glGetUniformLocation(program, "MaterialColor");

  /* Set the LightSourcePosition uniform which is constant throught the program */
  glUniform4fv(LightSourcePosition_location, 1, LightSourcePosition);

  /* make the gears */
  // static struct nidza_gear *
  // nidza_create_gear(GLfloat inner_radius, GLfloat outer_radius, GLfloat width, GLint teeth, GLfloat tooth_depth)
  nidza_gear1 = nidza_create_gear(0.3, 1.0, 1.0, 15, 0.5);

  // gear2 = create_gear(1.5, 2.0, 2.0, 10, 0.7);

  // gear3 = create_gear(1.3, 2.0, 0.5, 10, 0.7);


}
