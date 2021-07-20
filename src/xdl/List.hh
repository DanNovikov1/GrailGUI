#pragma once

#include "xdl/std.hh"

template <typename T>
class List : public CompoundType {
 private:
  DynArray<T> impl;

 public:
  List(const std::string listName, uint32_t size = 16)
      : CompoundType(listName), impl(size) {}
  DataType getDataType() const { return DataType::LIST16; }

  template <typename U>
  U deref(U& obj) {
    return obj;
  }

  template <typename U>
  U deref(U* obj) {
    if (obj == nullptr) {
      throw Ex1(Errcode::BAD_ARGUMENT);
    }
    return *obj;
  }

  template <typename U>
  void add(U e) {
    impl.add(deref(e));
  }

  template <class... Args>
  void add(Args&&... args) {
    (impl.add(deref(args)), ...);
  }
  uint32_t size() const override { return impl.size(); }
  uint32_t fieldSize() const override {
    if (impl.size() > 0) return impl[0].fieldSize();
    return 1;
  }
  void write(Buffer& buf) const override;
  void writeMeta(Buffer& buf) const override;
  void read(Buffer& buf) {
    uint32_t len = buf._readU16();
    T val;
    for (uint32_t i = 0; i < len; i++) {
      val.read(buf);
      add(val);
    }
  }
  void display(Buffer& binaryIn, Buffer& asciiOut) const override;
  void addMeta(ArrayOfBytes* meta) const override {
    throw Ex1(Errcode::UNIMPLEMENTED);
  }
  void addData(ArrayOfBytes* data) const override {
    throw Ex1(Errcode::UNIMPLEMENTED);
  }

  XDLType* begin(Buffer&) override;
};

template <typename T>
void List<T>::writeMeta(Buffer& buf) const {
  buf.write(DataType::LIST16);
  buf.write(XDLType::getTypeName());
  if (typeToDataType(impl[0]) != DataType::UNIMPL) {
    buf.write(typeToDataType(impl[0]));
  } else {  // if (is_base_of<XDLType, T>::value) {
    impl[0].writeMeta(buf);
  }
  // else {
  // buf.write(typeid(T).name());
  //}
}

template <typename T>
void List<T>::write(Buffer& buf) const {
  buf.write(uint16_t(impl.size()));
  for (uint32_t i = 0; i < impl.size(); i++) {
    if (typeToDataType(impl[i]) != DataType::UNIMPL) {
      buf.write(impl[i]);
    } else {
      impl[i].write(buf);
    }
    buf.checkAvailableWrite();
  }
}


// TODO: Implement
template <typename T>
void List<T>::display(Buffer& binaryIn, Buffer& asciiOut) const {}

template <typename T>
XDLType* List<T>::begin(Buffer& buf)  {return nullptr; } //TODO: templated lists cannot return generic pointers: &impl[0];}