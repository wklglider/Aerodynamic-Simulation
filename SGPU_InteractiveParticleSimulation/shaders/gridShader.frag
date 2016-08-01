in vec3 interpColor;
out vec4 fragColor;

void main(void) {
	fragColor = vec4(interpColor, 1.0f);
}
