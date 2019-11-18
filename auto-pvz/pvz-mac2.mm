#include "pvz-class.h"
#import <Cocoa/Cocoa.h>
void PvZ::WindowFront() {
    NSRunningApplication * app = [NSRunningApplication runningApplicationWithProcessIdentifier:pid];
    if (app != nil) {
        [app activateWithOptions:NSApplicationActivateIgnoringOtherApps];
    }
}
