#ifndef __IOD_MICRO_HELPER_H__
#define __IOD_MICRO_HELPER_H__

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
private: \
	TypeName(const TypeName&);               \
	void operator=(const TypeName&)

#define IMPLEMENT_SINGLETON_INSTANCE(TypeName)  TypeName __instance_of_##TypeName

#endif