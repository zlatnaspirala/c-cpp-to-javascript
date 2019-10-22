
/** The location of the shader uniforms */
static GLuint ModelViewProjectionMatrix_location,
    NormalMatrix_location,
    LightSourcePosition_location,
    MaterialColor_location;

/** The projection matrix */
static GLfloat ProjectionMatrix[16];

/** The direction of the directional light for the scene */
static const GLfloat LightSourcePosition[4] = {5.0, 5.0, 10.0, 1.0};

/**
 *  matrix calculation
 */

/**
 * Multiplies two 4x4 matrices.
 *
 * The result is stored in matrix m.
 *
 * @param m the first matrix to multiply
 * @param n the second matrix to multiply
 */
static void
multiply(GLfloat *m, const GLfloat *n)
{
  GLfloat tmp[16];
  const GLfloat *row, *column;
  div_t d;
  int i, j;

  for (i = 0; i < 16; i++)
  {
    tmp[i] = 0;
    d = div(i, 4);
    row = n + d.quot * 4;
    column = m + d.rem;
    for (j = 0; j < 4; j++)
      tmp[i] += row[j] * column[j * 4];
  }
  memcpy(m, &tmp, sizeof tmp);
}

/**
 * Rotates a 4x4 matrix.
 *
 * @param[in,out] m the matrix to rotate
 * @param angle the angle to rotate
 * @param x the x component of the direction to rotate to
 * @param y the y component of the direction to rotate to
 * @param z the z component of the direction to rotate to
 */
static void
rotate(GLfloat *m, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
  double s, c;

  sincos(angle, &s, &c);
  GLfloat r[16] = {
      x * x * (1 - c) + c, y * x * (1 - c) + z * s, x * z * (1 - c) - y * s, 0,
      x * y * (1 - c) - z * s, y * y * (1 - c) + c, y * z * (1 - c) + x * s, 0,
      x * z * (1 - c) + y * s, y * z * (1 - c) - x * s, z * z * (1 - c) + c, 0,
      0, 0, 0, 1};

  multiply(m, r);
}

/**
 * Translates a 4x4 matrix.
 *
 * @param[in,out] m the matrix to translate
 * @param x the x component of the direction to translate to
 * @param y the y component of the direction to translate to
 * @param z the z component of the direction to translate to
 */
static void
translate(GLfloat *m, GLfloat x, GLfloat y, GLfloat z)
{
  GLfloat t[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1};

  multiply(m, t);
}

/**
 * Creates an identity 4x4 matrix.
 *
 * @param m the matrix make an identity matrix
 */
static void
identity(GLfloat *m)
{
  GLfloat t[16] = {
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
      0.0,
      0.0,
      0.0,
      0.0,
      1.0,
  };

  memcpy(m, t, sizeof(t));
}

/**
 * Transposes a 4x4 matrix.
 *
 * @param m the matrix to transpose
 */
static void
transpose(GLfloat *m)
{
  GLfloat t[16] = {
      m[0], m[4], m[8], m[12],
      m[1], m[5], m[9], m[13],
      m[2], m[6], m[10], m[14],
      m[3], m[7], m[11], m[15]};

  memcpy(m, t, sizeof(t));
}

/**
 * Inverts a 4x4 matrix.
 *
 * This function can currently handle only pure translation-rotation matrices.
 * Read http://www.gamedev.net/community/forums/topic.asp?topic_id=425118
 * for an explanation.
 */
static void
invert(GLfloat *m)
{
  GLfloat t[16];
  identity(t);

  // Extract and invert the translation part 't'. The inverse of a
  // translation matrix can be calculated by negating the translation
  // coordinates.
  t[12] = -m[12];
  t[13] = -m[13];
  t[14] = -m[14];

  // Invert the rotation part 'r'. The inverse of a rotation matrix is
  // equal to its transpose.
  m[12] = m[13] = m[14] = 0;
  transpose(m);

  // inv(m) = inv(r) * inv(t)
  multiply(m, t);
}

/**
 * Calculate a perspective projection transformation.
 *
 * @param m the matrix to save the transformation in
 * @param fovy the field of view in the y direction
 * @param aspect the view aspect ratio
 * @param zNear the near clipping plane
 * @param zFar the far clipping plane
 */
void perspective(GLfloat *m, GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
  GLfloat tmp[16];
  identity(tmp);

  double sine, cosine, cotangent, deltaZ;
  GLfloat radians = fovy / 2 * M_PI / 180;

  deltaZ = zFar - zNear;
  sincos(radians, &sine, &cosine);

  if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
    return;

  cotangent = cosine / sine;

  tmp[0] = cotangent / aspect;
  tmp[5] = cotangent;
  tmp[10] = -(zFar + zNear) / deltaZ;
  tmp[11] = -1;
  tmp[14] = -2 * zNear * zFar / deltaZ;
  tmp[15] = 0;

  memcpy(m, tmp, sizeof(tmp));
}
