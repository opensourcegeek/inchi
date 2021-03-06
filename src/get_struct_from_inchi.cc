/* get_struct_from_inchi.cc
 * Copyright 2014 Cubane Canada, Inc.
 *
 * Released under the MIT license -- see MIT-LICENSE for details
 */

#include <nan.h>

#include "./using_v8.h"

#include "./get_struct_from_inchi_data.h"
#include "./get_struct_from_inchi_worker.h"

#include "./inchi_stereo.h"

#include "./inchi_queue.h"

void addstring(Handle<Object> ret, const char * name, const char * value);

NAN_METHOD(GetStructFromINCHI) {
  NanScope();

  size_t inchiLen = 0;
  char * inchi =
    reinterpret_cast<char *>(NanRawString(args[0], Nan::ASCII,
                                          &inchiLen, NULL, 0, 0));

  NanCallback * callback = new NanCallback(args[1].As<Function>());

  std::string inchiS(inchi, inchiLen);

  Enqueue(new GetStructFromINCHIWorker(callback, inchiS));

  delete[] inchi;

  NanReturnUndefined();
}

static Handle<Object> MakeBond(const inchi_Atom& a, int n) {
  NanScope();

  Handle<Object> ret = NanNewLocal<Object>(Object::New());

  ret->Set(NanSymbol("neighbor"), Number::New(a.neighbor[n]));
  ret->Set(NanSymbol("bond_type"), Number::New(a.bond_type[n]));
  ret->Set(NanSymbol("bond_stereo"), Number::New(a.bond_stereo[n]));

  return scope.Close(ret);
}

static Handle<Object> MakeAtom(const inchi_Atom& a) {
  NanScope();

  Handle<Object> ret = NanNewLocal<Object>(Object::New());

  ret->Set(NanSymbol("x"), Number::New(a.x));
  ret->Set(NanSymbol("y"), Number::New(a.y));
  ret->Set(NanSymbol("z"), Number::New(a.z));
  addstring(ret, "elname", a.elname);

  // compress neighbor, bond_type, and bond_stereo arrays
  ret->Set(NanSymbol("bonds"), Array::New());
  Local<Array> bonds = ret->Get(NanSymbol("bonds")).As<Array>();
  for (int i = 0; i < a.num_bonds; i += 1) {
    bonds->Set(i, MakeBond(a, i));
  }

  // implicit hydrogens
  ret->Set(NanSymbol("num_iso_H"), Array::New());
  Local<Array> num_iso_H = ret->Get(NanSymbol("num_iso_H")).As<Array>();
  for (int i = 0; i < NUM_H_ISOTOPES+1; i += 1) {
    num_iso_H->Set(i, Number::New(a.num_iso_H[i]));
  }

  ret->Set(NanSymbol("isotopic_mass"), Number::New(a.isotopic_mass));
  ret->Set(NanSymbol("radical"), Number::New(a.radical));
  ret->Set(NanSymbol("charge"), Number::New(a.charge));

  return scope.Close(ret);
}

Handle<Object> MakeStereo0D(const inchi_Stereo0D& stereo) {
  NanScope();

  Local<Object> ret = NanNewLocal<Object>(Object::New());

  Local<Array> neighbor = NanNewLocal<Array>(Array::New(STEREO0D_NEIGHBORS));
  for (int i = 0; i < STEREO0D_NEIGHBORS; i += 1) {
    neighbor->Set(i, Number::New(stereo.neighbor[i]));
  }
  ret->Set(NanSymbol("neighbor"), neighbor);

  ret->Set(NanSymbol("central_atom"), Number::New(stereo.central_atom));
  ret->Set(NanSymbol("type"), Number::New(stereo.type));
  ret->Set(NanSymbol("parity"), Number::New(stereo.parity));

  return scope.Close(ret);
}

Handle<Object> MakeStructure(const GetStructFromINCHIData& data) {
  NanScope();

  Handle<Object> ret = NanNewLocal<Object>(Object::New());

  // atom -- array of atom objects
  ret->Set(NanSymbol("atom"), Array::New(data.out_.num_atoms));
  Local<Array> atom = ret->Get(NanSymbol("atom")).As<Array>();
  for (int i = 0; i < data.out_.num_atoms; i += 1) {
    atom->Set(i, MakeAtom(data.out_.atom[i]));
  }

  // stereo0D -- array of stereo0D objects
  Local<Array> stereo0D = Array::New(data.out_.num_stereo0D);
  for (int i = 0; i < data.out_.num_stereo0D; i += 1) {
    stereo0D->Set(i, MakeStereo0D(data.out_.stereo0D[i]));
  }
  ret->Set(NanSymbol("stereo0D"), stereo0D);

  // message
  addstring(ret, "message", data.out_.szMessage);

  // log
  addstring(ret, "log", data.out_.szLog);

  // return code
  ret->Set(NanSymbol("result"), Number::New(data.result_));

  // warning flags
  Local<Array> flags = Array::New(2);
  flags->Set(0, Array::New(2));
  flags->Set(1, Array::New(2));

  for (int x = 0; x < 2; x += 1) {
    for (int y = 0; y < 2; y += 1) {
      Local<Value> flag = Number::New(data.out_.WarningFlags[x][y]);
      flags->Get(x).As<Array>()->Set(y, flag);
    }
  }

  ret->Set(NanSymbol("WarningFlags"), flags);

  return scope.Close(ret);
}
