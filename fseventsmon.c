
#include <stdio.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>


FSEventStreamRef stream_ref;

#define FLAG(flag) \
    if ((flags & kFSEventStreamEventFlag ## flag) == kFSEventStreamEventFlag ## flag) { \
        if (*buf) strcat(buf, " "); \
        strcat(buf, #flag); \
    }
static void FSEventStreamEventFlagsToString(char *buf, FSEventStreamEventFlags flags) {
    if (flags == kFSEventStreamEventFlagNone) {
        strcpy(buf, "None");
    } else {
        *buf = 0;
        FLAG(MustScanSubDirs);
        FLAG(UserDropped);
        FLAG(KernelDropped);
        FLAG(EventIdsWrapped);
        FLAG(HistoryDone);
        FLAG(RootChanged);
        FLAG(Mount);
        FLAG(Unmount);
        FLAG(ItemCreated);
        FLAG(ItemRemoved);
        FLAG(ItemInodeMetaMod);
        FLAG(ItemRenamed);
        FLAG(ItemModified);
        FLAG(ItemFinderInfoMod);
        FLAG(ItemChangeOwner);
        FLAG(ItemXattrMod);
        FLAG(ItemIsFile);
        FLAG(ItemIsDir);
        FLAG(ItemIsSymlink);
    }
}

static void FSMonitorEventStreamCallback(ConstFSEventStreamRef streamRef, void *context, size_t numEvents, const char **eventPaths, const FSEventStreamEventFlags eventFlags[], const FSEventStreamEventId eventIds[]) {
    static char buf[10240];
    int i;
    for (i = 0; i < numEvents; i++) {
        FSEventStreamEventFlagsToString(buf, eventFlags[i]);
        printf("%s  (%s)\n", eventPaths[i], buf);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: fseventsmon /path/to/folder\n");
        exit(10);
    }

    const char *path = argv[1];

    CFStringRef path_ref = CFStringCreateWithCString(NULL, path, kCFStringEncodingUTF8);
    CFArrayRef paths_ref = CFArrayCreate(NULL, (const void **) &path_ref, 1, &kCFTypeArrayCallBacks);

    stream_ref = FSEventStreamCreate(NULL,
                                     (FSEventStreamCallback)FSMonitorEventStreamCallback,
                                     NULL,
                                     paths_ref,
                                     kFSEventStreamEventIdSinceNow,
                                     0.05,
                                     0);
    if (!stream_ref) {
        printf("Failed to start monitoring of %s (FSEventStreamCreate error)\n", path);
        exit(1);
    }

    FSEventStreamScheduleWithRunLoop(stream_ref, CFRunLoopGetMain(), kCFRunLoopDefaultMode);
    if (!FSEventStreamStart(stream_ref)) {
        printf("Failed to start monitoring of %s (FSEventStreamStart error)\n", path);
    }

    printf("Monitoring %s...\n", path);
    CFRunLoopRun();

    return 0;
}
