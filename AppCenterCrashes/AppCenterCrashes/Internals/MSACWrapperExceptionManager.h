// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#import <Foundation/Foundation.h>

@class MSACWrapperException;

/**
 * This class helps wrapper SDKs augment crash reports with additional data.
 *
 * HOW IT WORKS:
 * 1. Application is crashing from a wrapper SDK, but before propagating crash to the native code, it calls "saveWrapperException" which
 * saves the MSACWrapperException to a file called "last_saved_wrapper_exception".
 * 2. On startup, the native SDK must find that file if it exists, and use the MSACWrapperException's "pid" to correlate the file to a
 * PLCrashReport on disk. If a match is found, the file is renamed to the UUID of the PLCrashReport.
 * 3. When an MSACAppleErrorLog must be generated, a corresponding MSACWrapperException file is searched for, and if found, its
 * MSACWrapperExceptionModel property is added to the MSACAppleErrorLog. The file is not deleted because there is an additional "data" property
 * that contains information that the wrapper SDK may want.
 * 4. When an MSACErrorReport equivalent needs to be generated by a wrapper SDK, it is identical to the actual MSACErrorReport, but also
 * includes the additional data that was saved. This data is accessed by "loadWrapperExceptionWithUUID".
 * Thus, the file on disk can only be deleted after all crash callbacks with an MSACErrorReport parameter have completed.
 */
@interface MSACWrapperExceptionManager : NSObject

/**
 * Save the MSACWrapperException to the file "last_saved_wrapper_exception". This should only be used by a wrapper SDK; native code has no
 * use for it.
 */
+ (void)saveWrapperException:(MSACWrapperException *)wrapperException;

/**
 * Load a wrapper exception from disk with a given UUID.
 */
+ (MSACWrapperException *)loadWrapperExceptionWithUUIDString:(NSString *)uuidString;

@end
