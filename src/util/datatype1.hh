// This file was generated by a python script.
// Do not edit this file... YOUR CHANGES WILL GET OVERWRITTEN...
// Edit proj/xdl_types.json instead.
#pragma once

#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

/*
   The list of XDL types specific to this application.
   Note: When a comment says 'n byte length' it means that the type
         has 2^(8*n) elements
 */
enum class DataType {
  U8,         // unsigned int 0..255
  U16,        // unsigned int 0..65535
  U24,        // unsigned int 0..16*1024*1024
  U32,        // unsigned int 0..(2^32)-1
  U64,        // unsigned int 0..(2^64)-1
  U128,       // unsigned int 0..(2^128)-1
  U256,       // unsigned int 0..(2^256)-1
  I8,         // signed int -128..127
  I16,        // signed int -32768..32767
  I24,        // signed int -8388608..8388607
  I32,        // signed int -(2^31)..(2^31)-1
  I64,        // signed int -(2^63)..(2^63)-1
  I128,       // signed int -(2^127)..(2^127)-1
  I256,       // signed int -(2^255)..(2^255)-1
  F32,        // single-precision floating point 1.175e-38..3.403e+38
  F64,        // double-precision floating point 2.225e-308..1.798e+308
  BOOL,       // true/false, normally 1 byte but arrays should use 1 bit
  DATE,       // 32 bit date relative to J2000 (integer)
  JULDATE,    // scientific date relative to J2000 (double)
  TIMESTAMP,  // typical unix timestamp
  STRING8,    // string of 1 byte length, each char is 1 byte
  STRING16,   // string of 2 byte length, each char is 1 byte
  STRING32,   // string of 4 byte length, each char is 1 byte
  STRING64,   // string of 8 byte length, each char is 1 byte
  UTF8_8,    // international string of 1 byte length, each char is 1 or 2 bytes
  UTF8_16,   // international string of 2 byte length, each char is 1 or 2 bytes
  UTF8_32,   // international string of 4 byte length, each char is 1 or 2 bytes
  UTF8_64,   // international string of 8 byte length, each char is 1 or 2 bytes
  UTF16_8,   // international string of 1 byte length, each char is 2 bytes
  UTF16_16,  // international string of 2 byte length, each char is 2 bytes
  UTF16_32,  // international string of 4 byte length, each char is 2 bytes
  UTF16_64,  // international string of 8 byte length, each char is 2 bytes
  REGEX,     // string representing a regular expression
  LIST8,     // list with 1 byte length
  LIST16,    // list with 2 byte length
  LIST32,    // list with 4 byte length
  LIST64,    // list with 8 byte length
  STRUCT8,   // struct with 1 byte length of records
  STRUCT16,  // struct with 2 byte length of records
  STRUCT32,  // struct with 4 byte length of records
  DYNAMICLIST8,  // list from dynamic sources (e.x. server). Provides a length
                 // at transmission time (at most 1 byte length)
  DYNAMICLIST16,  // list from dynamic sources (e.x. server). Provices a length
                  // at transmissoin time (at most 2 byte length)
  FUNC8,       // function with up to 1 byte length of instructions
  FUNC16,      // function with up to 2 byte length of instructions
  FUNCPARAM8,  // function with up to 1 byte length of parameters and 1 byte
               // length of instructions
  FUNCPARAM16,  // function with up to 2 byte length of parameters and 2 byte
                // length of instructions
  LOOP1,      // repeat up to 1 byte length times
  LOOP2,      // repeat up to 2 byte length times
  LOOP4,      // repeat up to 4 byte length times
  BITVEC8,    // bit vector of 1 byte length
  BITVEC16,   // bit vector of 2 byte length
  BITVEC32,   // bit vector of 4 byte length
  BITVEC64,   // bit vector of 8 byte length
  BV32,       // 32 bits stored in a 4 byte integer
  BV64,       // 64 bits stored in a 8 byte integer
  BITFIELDS,  // 4 byte size, 1 byte bit size (for storing small numbers packed
              // bitfields)
  ARITHMETIC,  // arithmetic encoding of numbers specify range and size (4 bytes
               // each)
  JPEG,      // Allows embedding of jpegs into stream
  JPEGLIST,  // 4 byte number of jpegs, then a single header, then multiple
             // files of the same size
  BLOB16,     // block of binary data of 2 byte length
  BLOB32,     // block of binary data of 4 byte length
  BLOB64,     // block of binary data of 8 byte length
  BIGINT,     // container for big integers
  OK,         // Success value for result types
  ERR,        // Wrapper for error propogation
  SOME,       // Wrapper for optional or result values
  NONE,       // Empty container (null without the pointers)
  OPTIONAL,   // Contains either Some(T) or None
  RESULT,     // Contains either Ok(T) or Err(E)
  TYPEDEF,    // allows aliasing of XDL types
  UNIMPL,     // allows error handling for unimplemented types or functionality
  ENUM_SIZE,  // sentinel for running over the enum length
};

extern const char* DataTypeNames[];
extern std::unordered_map<std::string, DataType> mapnames;
extern void loadmap();