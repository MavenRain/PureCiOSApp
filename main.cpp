//
//  main.cpp
//  AsmTest
//
//  Created by SolomonRain on 7/26/16.
//  Copyright © 2016 TheObiGLLC. All rights reserved.
//

#include <objc/message.h>
#include <CoreGraphics/CoreGraphics.h>
#ifdef __cplusplus
extern "C" {
#endif
    int UIApplicationMain(int, const char * *, id, id);
#ifdef __cplusplus
}
#endif

BOOL didFinishLaunching(id self, SEL cmd, void * application, void * options)
{
    auto window = reinterpret_cast<id(*)(id, SEL)>(objc_msgSend)(reinterpret_cast<id>(objc_getClass("UIWindow")), sel_getUid("alloc"));
    auto screen = reinterpret_cast<id(*)(id, SEL)>(objc_msgSend)(reinterpret_cast<id>(objc_getClass("UIScreen")), sel_getUid("mainScreen"));
    auto bounds = reinterpret_cast<CGRect(*)(id, SEL)>(objc_msgSend)(screen, sel_getUid("bounds"));
    window = reinterpret_cast<id(*)(id, SEL, CGRect)>(objc_msgSend)(window, sel_getUid("initWithFrame:"), bounds);
    auto green = reinterpret_cast<id(*)(id, SEL)>(objc_msgSend)(reinterpret_cast<id>(objc_getClass("UIColor")), sel_getUid("greenColor"));
    reinterpret_cast<void(*)(id, SEL, id)>(objc_msgSend)(window, sel_getUid("setBackgroundColor:"), green);
    auto viewController = reinterpret_cast<id(*)(id, SEL)>(objc_msgSend)(reinterpret_cast<id>(objc_getClass("UIViewController")), sel_getUid("alloc"));
    viewController = reinterpret_cast<id(*)(id, SEL)>(objc_msgSend)(viewController, sel_getUid("init"));
    reinterpret_cast<void(*)(id, SEL, id)>(objc_msgSend)(window, sel_getUid("setRootViewController:"), viewController);
    reinterpret_cast<void(*)(id, SEL)>(objc_msgSend)(window, sel_getUid("makeKeyAndVisible"));
    return YES;
}

int main(int argc, const char * * argv)
{
    auto appDelClass = objc_allocateClassPair(objc_getClass("UIResponder"), "AppDelegate", 0);
    class_addIvar(appDelClass, "window", sizeof(id), 0, "@");
    class_replaceMethod(appDelClass, sel_getUid("application:didFinishLaunchingWithOptions:"), reinterpret_cast<IMP>(didFinishLaunching), "i@:??");
    objc_registerClassPair(appDelClass);
    auto appDelegate = reinterpret_cast<id(*)(id, SEL, const char *)>(objc_msgSend)(reinterpret_cast<id>(objc_getClass("NSString")), sel_getUid("stringWithUTF8String:"), "AppDelegate");
    return UIApplicationMain(argc, argv, nil, appDelegate);
}
