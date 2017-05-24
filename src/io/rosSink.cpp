/*F***************************************************************************
 *
 * openSMILE - the Munich open source Multimedia Interpretation by
 * Large-scale Extraction toolkit
 *
 * This file is part of openSMILE.
 *
 * openSMILE is copyright (c) by audEERING GmbH. All rights reserved.
 *
 * See file "COPYING" for details on usage rights and licensing terms.
 * By using, copying, editing, compiling, modifying, reading, etc. this
 * file, you agree to the licensing terms in the file COPYING.
 * If you do not agree to the licensing terms,
 * you must immediately destroy all copies of this file.
 *
 * THIS SOFTWARE COMES "AS IS", WITH NO WARRANTIES. THIS MEANS NO EXPRESS,
 * IMPLIED OR STATUTORY WARRANTY, INCLUDING WITHOUT LIMITATION, WARRANTIES OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, ANY WARRANTY AGAINST
 * INTERFERENCE WITH YOUR ENJOYMENT OF THE SOFTWARE OR ANY WARRANTY OF TITLE
 * OR NON-INFRINGEMENT. THERE IS NO WARRANTY THAT THIS SOFTWARE WILL FULFILL
 * ANY OF YOUR PARTICULAR PURPOSES OR NEEDS. ALSO, YOU MUST PASS THIS
 * DISCLAIMER ON WHENEVER YOU DISTRIBUTE THE SOFTWARE OR DERIVATIVE WORKS.
 * NEITHER TUM NOR ANY CONTRIBUTOR TO THE SOFTWARE WILL BE LIABLE FOR ANY
 * DAMAGES RELATED TO THE SOFTWARE OR THIS LICENSE AGREEMENT, INCLUDING
 * DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL OR INCIDENTAL DAMAGES, TO THE
 * MAXIMUM EXTENT THE LAW PERMITS, NO MATTER WHAT LEGAL THEORY IT IS BASED ON.
 * ALSO, YOU MUST PASS THIS LIMITATION OF LIABILITY ON WHENEVER YOU DISTRIBUTE
 * THE SOFTWARE OR DERIVATIVE WORKS.
 *
 * Main authors: Florian Eyben, Felix Weninger,
 * 	      Martin Woellmer, Bjoern Schuller
 *
 * Copyright (c) 2008-2013,
 *   Institute for Human-Machine Communication,
 *   Technische Universitaet Muenchen, Germany
 *
 * Copyright (c) 2013-2015,
 *   audEERING UG (haftungsbeschraenkt),
 *   Gilching, Germany
 *
 * Copyright (c) 2016,
 *   audEERING GmbH,
 *   Gilching Germany
 ***************************************************************************E*/

#include <io/rosSink.hpp>
#define MODULE "cRosSink"

SMILECOMPONENT_STATICS(cRosSink)

SMILECOMPONENT_REGCOMP(cRosSink)
{
  SMILECOMPONENT_REGCOMP_INIT
  scname = COMPONENT_NAME_CROSSINK;
  sdescription = COMPONENT_DESCRIPTION_CROSSINK;

  // we inherit cDataSink configType and extend it:
  SMILECOMPONENT_INHERIT_CONFIGTYPE("cDataSink")

    SMILECOMPONENT_IFNOTREGAGAIN_BEGIN
    ct->setField("logfile","Ros logfile (default=(null) : no log file)",(const char*)NULL);

  SMILECOMPONENT_IFNOTREGAGAIN_END

    SMILECOMPONENT_MAKEINFO(cRosSink);
}

SMILECOMPONENT_CREATE(cRosSink)

//-----

cRosSink::cRosSink(const char *_name) :
cDataSink(_name),
logfile(NULL)
{
}

void cRosSink::fetchConfig()
{
  cDataSink::fetchConfig();

  logfile = getStr("logfile");
  if (logfile != NULL) { SMILE_IDBG(2,"Ros logfile = '%s'",logfile); }
}


int cRosSink::myFinaliseInstance()
{
  int ret = cDataSink::myFinaliseInstance();
  return ret;
}

/* code to receive and process turnStart and turnEnd messages */
int cRosSink::processComponentMessage( cComponentMessage *_msg )
{
  if (isMessageType(_msg,"classificationResult")) {
    SMILE_PRINT("RECEIVED MESSAGE IN ROS SINK");
    SMILE_PRINT("RESULT: '%s'", _msg->msgtext);
  }
  return 0;
}

cRosSink::~cRosSink()
{
}
