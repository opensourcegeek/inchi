/*
 * International Chemical Identifier (InChI)
 * Version 1
 * Software version 1.04
 * September 9, 2011
 *
 * The InChI library and programs are free software developed under the
 * auspices of the International Union of Pure and Applied Chemistry (IUPAC).
 * Originally developed at NIST. Modifications and additions by IUPAC 
 * and the InChI Trust.
 *
 * IUPAC/InChI-Trust Licence No.1.0 for the 
 * International Chemical Identifier (InChI) Software version 1.04
 * Copyright (C) IUPAC and InChI Trust Limited
 * 
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the IUPAC/InChI Trust InChI Licence No.1.0, 
 * or any later version.
 * 
 * Please note that this library is distributed WITHOUT ANY WARRANTIES 
 * whatsoever, whether expressed or implied.  See the IUPAC/InChI Trust 
 * Licence for the International Chemical Identifier (InChI) Software 
 * version 1.04, October 2011 ("IUPAC/InChI-Trust InChI Licence No.1.0") 
 * for more details.
 * 
 * You should have received a copy of the IUPAC/InChI Trust InChI 
 * Licence No. 1.0 with this library; if not, please write to:
 * 
 * The InChI Trust
 * c/o FIZ CHEMIE Berlin
 *
 * Franklinstrasse 11
 * 10587 Berlin
 * GERMANY
 *
 * or email to: ulrich@inchi-trust.org.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#include "e_mode.h"
#include "e_ctl_data.h"

#include "inchi_api.h"
#include "e_ichi_io.h"
#include "e_ichi_parms.h"
#include "e_util.h"
#include "e_ichicomp.h"

#define DetectInputINChIFileType e_DetectInputINChIFileType
#define ReadCommandLineParms     e_ReadCommandLineParms
#define mystrncpy                e_mystrncpy


#define LtrimRtrim               e_LtrimRtrim
#define PrintInputParms          e_PrintInputParms
#define OpenFiles                e_OpenFiles
#define PrintFileName            e_PrintFileName

/*^^^ */
#define HelpCommandLineParms     e_HelpCommandLineParms
#define HelpCommandLineParmsReduced    e_HelpCommandLineParmsReduced
/*^^^ */



#include "../inchi_dll/ichiparm.h"

