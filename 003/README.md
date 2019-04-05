# 003
loads the dynamic shared object

## graph
                    main
                     |  
                     v
                  module (dlopen)
                     |
                     v
             external_module

## reference
dlopen(3), dlsym(3), dladdr(3), dlerror(3), dlinfo(3), ld.so(8)

