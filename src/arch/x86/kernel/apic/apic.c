/*
 *   The OpenLoader project - Local APIC interface
 *   Copyright (C) 2011  Michel Megens
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include <arch/x86/cpu.h>
#include <arch/x86/apic/apic.h>

#include <sys/sys.h>

#include <text.h>

struct apic* apic;

static int 
ol_detect_apic(ol_cpu_t cpu)
{
  cpu->lock(&cpu_lock);
  if((cpu->flags & 0x1))
  {
    ol_gen_registers_t regs = ol_cpuid(1);
    if(regs->edx & (1<<9))
    {
      /* apic is available */
      cpu->unlock(&cpu_lock);
      return 0;
    }
    cpu->unlock(&cpu_lock);
    return -1;
  }
}

int
ol_apic_init(ol_cpu_t cpu)
{
  if(!ol_detect_apic(cpu))
  {
    println("Apic detected");
  }
  else
    goto fail;
  
  struct ol_madt_apic* acpiapic;
  int i = 0;
//   while((acpiapic+i) != NULL) i++;
  
  for(i = 0, acpiapic = acpi_get_apic(); *((void**)acpiapic+i) != NULL; i++) 
  {
#ifdef __APIC_DBG
    printf("%x\t%i\n", acpiapic+i, acpiapic[i].length);
#endif
  }
  
  return 0;
  fail:
    return -1;
}
