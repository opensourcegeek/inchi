#ifndef SRC_MOLECULE_WRAP_H_
#define SRC_MOLECULE_WRAP_H_
/* molecule_wrap.h
 * Copyright 2014 Cubane Canada, Inc.
 *
 * Released under the MIT license -- see MIT-LICENSE for details
 */

#include <nan.h>

#include "./molecule.h"
#include "./using_v8.h"

struct Molecule_wrap {
  explicit Molecule_wrap(Handle<Value> in);
  ~Molecule_wrap() {}

  void addAtoms(Handle<Value> atoms);
  void addBonds(Handle<Value> bonds);
  void addStereo(Handle<Value> stereo);

  Molecule mol;
};

NAN_METHOD(GetINCHI);

#endif  // SRC_MOLECULE_WRAP_H_
