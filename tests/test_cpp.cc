/*
 * upb - a minimalist implementation of protocol buffers.
 *
 * Copyright (c) 2011 Google Inc.  See LICENSE for details.
 * Author: Josh Haberman <jhaberman@gmail.com>
 *
 * Tests for C++ wrappers.
 */

#include <stdio.h>
#include <iostream>
#include "upb/bytestream.hpp"
#include "upb/def.hpp"
#include "upb/handlers.hpp"
#include "upb/upb.hpp"
#include "upb/pb/decoder.hpp"
#include "upb/pb/glue.hpp"
#include "upb_test.h"

static void TestSymbolTable(const char *descriptor_file) {
  upb::SymbolTable *s = upb::SymbolTable::New(&s);
  upb::Status status;
  if (!upb::LoadDescriptorFileIntoSymtab(s, descriptor_file, &status)) {
    std::cerr << "Couldn't load descriptor: " << status;
    exit(1);
  }
  const upb::MessageDef *md = s->LookupMessage("A", &md);
  ASSERT(md);

  s->Unref(&s);
  md->Unref(&md);
}

static void TestByteStream() {
  upb::StringSource stringsrc;
  stringsrc.Reset("testing", 7);
  upb::ByteRegion* byteregion = stringsrc.AllBytes();
  ASSERT(byteregion->FetchAll() == UPB_BYTE_OK);
  char* str = byteregion->StrDup();
  ASSERT(strcmp(str, "testing") == 0);
  free(str);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: test_cpp <descriptor file>\n");
    return 1;
  }
  TestSymbolTable(argv[1]);
  TestByteStream();
  return 0;
}
