/* load nitf from a file
 *
 * 28/03/2021
 * 	- from nitro
 */

/*

    This file is part of VIPS.
    
    VIPS is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301  USA

 */

/*

    These files are distributed with VIPS - http://www.vips.ecs.soton.ac.uk

 */

/*
#define DEBUG
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /*HAVE_CONFIG_H*/
#include <vips/intl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <vips/vips.h>
#include <vips/buf.h>
#include <vips/internal.h>

#include "pforeign.h"

#if defined(HAVE_NITRO)

typedef struct _VipsForeignLoadNitro
{
    VipsForeignLoad parent_object;

    char *filename;
} VipsForeignLoadNitro;

typedef VipsForeignLoadClass VipsForeignLoadNitroClass;

G_DEFINE_TYPE( VipsForeignLoadNitro, vips_foreign_load_nitro, VIPS_TYPE_FOREIGN_LOAD);

static VipsForeignFlags vips_foreign_load_nitro_get_flags_filename(const char *filename)
{
    VipsForeignFlags flags;

    flags = 0;
    if (vips__nitro_isinterlaced(filename))
        flags = VIPS_FOREIGN_PARTIAL;
    else
        flags = VIPS_FOREIGN_SEQUENTIAL;

    return flags;
}

static VipsForeignFlags vips_foreign_load_nitro_get_flags(VipsForeignLoad *load)
{
    VipsForeignLoadNitro *nitro = (VipsForeignLoadNitro *) load;

    return vips_foreign_load_nitro_get_flags_filename(nitro->filename);
}

static int vips_foreign_load_header(VipsForeignLoad *load)
{
    VipsForeignLoadNitro *nitro = (VipsForeignLoadNitro *)load;

    if (vips__nitro_header(nitro->filename, load->real))
        return 1;

    return 0;
}

static int vips_foreign_load_nitro_load(VipsForeignLoad *load)
{
    VipsForeignLoadNitro *nitro = (VipsForeignLoadNitro *)load;

    if (vips__nitro_read(nitro->filename, load->real))
        return -1;

    return 0;
}


#endif /* defined(HAVE_NITRO)