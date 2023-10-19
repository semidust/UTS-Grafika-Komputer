uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

layout (location = 0) out vec4 color;
varying vec2 vPos;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
	
	float distance = length(vPos);

	if (distance <= 0.8)
	{
		color = vec4(1.0, 1.0, 1.0, 1.0);
	}

	float dotSecond = dot(normalize(vPos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));
	if (distance >= 0.3 && distance <= 0.4 && dotSecond < sin(currentSecondPointer))
	{
			color = vec4(0.0, 0.0, 1.0, 1.0);
	}

	// menit
	float dotMinute = dot(normalize(vPos),  vec2(cos(currentMinutePointer), sin(currentMinutePointer)));
	
	if (distance <= 0.6 && dotMinute > 0.995)
	{
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}

	// jam
	float dotHour = dot(normalize(vPos),  vec2(cos(currentHourPointer), sin(currentHourPointer)));

	if (distance <= 0.5 && dotHour > 0.99)
	{
		color = vec4(1.0, 0.0, 0.0, 1.0);
	}

}