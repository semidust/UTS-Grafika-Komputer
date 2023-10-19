layout (location = 0) out vec4 color;
varying vec2 vPos;

void main()
{
	color = vec4(0.0, 0.0, 0.0, 1.0);
	
	float distance = length(vPos);

	if (distance <= 0.8) {

	color = vec4(1.0, 1.0, 1.0, 1.0);

	}
}