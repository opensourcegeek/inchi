#ifndef SRC_GET_STRUCT_FROM_INCHI_WORKER_H_
#define SRC_GET_STRUCT_FROM_INCHI_WORKER_H_
/* get_struct_from_inchi_worker.h
 * Copyright 2014 Cubane Canada, Inc.
 *
 * Released under the MIT license -- see MIT-LICENSE for details
 */

#include <nan.h>

#include <string>

#include "./inchi_queue.h"

/**
   This class, derived from NanAsyncWorker, manages
   asynhronous calls to GetStructFromINCHI

   @module Internal
   @class GetStructFromINCHIWorker
*/
struct GetStructFromINCHIWorker : public NanAsyncWorker {
  GetStructFromINCHIData data_;

  /**
     @method GetStructFromINCHIWorker
     @constructor
     @param {NanCallback *} callback Callback function to call when finished
     @param {std::string} inchi InChI string to convert
  */
  GetStructFromINCHIWorker(NanCallback * callback, const std::string& inchi) :
    NanAsyncWorker(callback), data_(inchi) {
  }

  /**
     @method ~GetStructFromINCHIWorker
  */
  ~GetStructFromINCHIWorker() {
  }

  /**
     Calls GetStructFromINCHI with thread-safe data

     @method Execute
  */
  void Execute();

  /**
     Constructs result value, passes it to callback
     @method
  */
  void HandleOKCallback();
};

#endif  // SRC_GET_STRUCT_FROM_INCHI_WORKER_H_
