#include "IDevice.h"

#if defined(OPENGL)
#include "OpenGL/OpenGLDevice.h"
using DeviceImpl = tabi::OpenGLDevice;
#else
#error No render device implementation specified for current platform
using DeviceImpl = tabi::IDevice;
#endif

tabi::IDevice* tabi::IDevice::GetInstance()
{
	static IDevice* device = new DeviceImpl;

	return device;
}
