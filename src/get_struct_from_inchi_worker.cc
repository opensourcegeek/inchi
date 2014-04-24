/* get_struct_from_inchi_worker.cc
 * Copyright 2014 Cubane Canada, Inc.
 *
 * Released under the MIT license -- see MIT-LICENSE for details
 */

#include <nan.h>

#include <string>

#include "./using_v8.h"

#include "./get_struct_from_inchi_data.h"
#include "./get_struct_from_inchi_worker.h"

#include "./inchi_queue.h"

Handle<Object> MakeStructure(const GetStructFromINCHIData& data);

void GetStructFromINCHIWorker::HandleOKCallback() {
  NanScope();

  Handle<Object> result = MakeStructure(data_);

  Handle<Value> argv[] = {
    v8::Null(),
    result
  };

  callback->Call(2, argv);
}

void GetStructFromINCHIWorker::Execute() {
  data_.GetStructFromINCHI();

  if (data_.result_ != inchi_Ret_OKAY &&
      data_.result_ != inchi_Ret_WARNING) {
    // TODO(SOM): would like to return result_ -- maybe on Error object?
    this->errmsg = strdup(data_.out_.szMessage);
  }

  QueueFinish();
}
