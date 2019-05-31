#include "MemoryProtection.h"

#include <link.h> // dl_iterate_phdr


/* Read Memory Protection without parsing /proc/$$/maps
 * Stack overflow btfo'd */
static int flags = 0;
static uintptr_t addr;
unsigned int MemoryProtection::GetProtectionFlags( uintptr_t address ) {
    flags = 0;
    addr = address;
    dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
        uintptr_t startingAddr = 0;
        uintptr_t endingAddr = 0;

        for( int i = 0; i < info->dlpi_phnum; i++ ){
            const ElfW(Phdr) *hdr = &info->dlpi_phdr[i];
            if( hdr->p_memsz ){
                startingAddr = info->dlpi_addr + hdr->p_vaddr;
                endingAddr = startingAddr + hdr->p_memsz;
                if( startingAddr <= addr && endingAddr >= addr ){
                    flags |= hdr->p_flags;
                }
            }
        }

        return 0;
    }, nullptr);

    return flags;
}