// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: config.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "config.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace test {

namespace {

const ::google::protobuf::Descriptor* first_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  first_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_config_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_config_2eproto() {
  protobuf_AddDesc_config_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "config.proto");
  GOOGLE_CHECK(file != NULL);
  first_descriptor_ = file->message_type(0);
  static const int first_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(first, a_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(first, b_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(first, c_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(first, d_),
  };
  first_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      first_descriptor_,
      first::default_instance_,
      first_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(first, _has_bits_[0]),
      -1,
      -1,
      sizeof(first),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(first, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_config_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      first_descriptor_, &first::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_config_2eproto() {
  delete first::default_instance_;
  delete first_reflection_;
}

void protobuf_AddDesc_config_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AddDesc_config_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\014config.proto\022\004test\"3\n\005first\022\t\n\001a\030\001 \002(\005"
    "\022\t\n\001b\030\002 \001(\r\022\t\n\001c\030\003 \001(\t\022\t\n\001d\030\004 \003(\r", 73);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "config.proto", &protobuf_RegisterTypes);
  first::default_instance_ = new first();
  first::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_config_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_config_2eproto {
  StaticDescriptorInitializer_config_2eproto() {
    protobuf_AddDesc_config_2eproto();
  }
} static_descriptor_initializer_config_2eproto_;

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int first::kAFieldNumber;
const int first::kBFieldNumber;
const int first::kCFieldNumber;
const int first::kDFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

first::first()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:test.first)
}

void first::InitAsDefaultInstance() {
}

first::first(const first& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:test.first)
}

void first::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  a_ = 0;
  b_ = 0u;
  c_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

first::~first() {
  // @@protoc_insertion_point(destructor:test.first)
  SharedDtor();
}

void first::SharedDtor() {
  c_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void first::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* first::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return first_descriptor_;
}

const first& first::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_config_2eproto();
  return *default_instance_;
}

first* first::default_instance_ = NULL;

first* first::New(::google::protobuf::Arena* arena) const {
  first* n = new first;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void first::Clear() {
// @@protoc_insertion_point(message_clear_start:test.first)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(first, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<first*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 7u) {
    ZR_(a_, b_);
    if (has_c()) {
      c_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }

#undef ZR_HELPER_
#undef ZR_

  d_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool first::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:test.first)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 a = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &a_)));
          set_has_a();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_b;
        break;
      }

      // optional uint32 b = 2;
      case 2: {
        if (tag == 16) {
         parse_b:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &b_)));
          set_has_b();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_c;
        break;
      }

      // optional string c = 3;
      case 3: {
        if (tag == 26) {
         parse_c:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_c()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->c().data(), this->c().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "test.first.c");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_d;
        break;
      }

      // repeated uint32 d = 4;
      case 4: {
        if (tag == 32) {
         parse_d:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 32, input, this->mutable_d())));
        } else if (tag == 34) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_d())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_d;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:test.first)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:test.first)
  return false;
#undef DO_
}

void first::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:test.first)
  // required int32 a = 1;
  if (has_a()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->a(), output);
  }

  // optional uint32 b = 2;
  if (has_b()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->b(), output);
  }

  // optional string c = 3;
  if (has_c()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->c().data(), this->c().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "test.first.c");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->c(), output);
  }

  // repeated uint32 d = 4;
  for (int i = 0; i < this->d_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      4, this->d(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:test.first)
}

::google::protobuf::uint8* first::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:test.first)
  // required int32 a = 1;
  if (has_a()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->a(), target);
  }

  // optional uint32 b = 2;
  if (has_b()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->b(), target);
  }

  // optional string c = 3;
  if (has_c()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->c().data(), this->c().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "test.first.c");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->c(), target);
  }

  // repeated uint32 d = 4;
  for (int i = 0; i < this->d_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(4, this->d(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:test.first)
  return target;
}

int first::ByteSize() const {
// @@protoc_insertion_point(message_byte_size_start:test.first)
  int total_size = 0;

  // required int32 a = 1;
  if (has_a()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->a());
  }
  if (_has_bits_[1 / 32] & 6u) {
    // optional uint32 b = 2;
    if (has_b()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->b());
    }

    // optional string c = 3;
    if (has_c()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->c());
    }

  }
  // repeated uint32 d = 4;
  {
    int data_size = 0;
    for (int i = 0; i < this->d_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->d(i));
    }
    total_size += 1 * this->d_size() + data_size;
  }

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void first::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:test.first)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  const first* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const first>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:test.first)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:test.first)
    MergeFrom(*source);
  }
}

void first::MergeFrom(const first& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:test.first)
  if (GOOGLE_PREDICT_FALSE(&from == this)) {
    ::google::protobuf::internal::MergeFromFail(__FILE__, __LINE__);
  }
  d_.MergeFrom(from.d_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_a()) {
      set_a(from.a());
    }
    if (from.has_b()) {
      set_b(from.b());
    }
    if (from.has_c()) {
      set_has_c();
      c_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.c_);
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void first::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:test.first)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void first::CopyFrom(const first& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:test.first)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool first::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;

  return true;
}

void first::Swap(first* other) {
  if (other == this) return;
  InternalSwap(other);
}
void first::InternalSwap(first* other) {
  std::swap(a_, other->a_);
  std::swap(b_, other->b_);
  c_.Swap(&other->c_);
  d_.UnsafeArenaSwap(&other->d_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata first::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = first_descriptor_;
  metadata.reflection = first_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// first

// required int32 a = 1;
bool first::has_a() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void first::set_has_a() {
  _has_bits_[0] |= 0x00000001u;
}
void first::clear_has_a() {
  _has_bits_[0] &= ~0x00000001u;
}
void first::clear_a() {
  a_ = 0;
  clear_has_a();
}
 ::google::protobuf::int32 first::a() const {
  // @@protoc_insertion_point(field_get:test.first.a)
  return a_;
}
 void first::set_a(::google::protobuf::int32 value) {
  set_has_a();
  a_ = value;
  // @@protoc_insertion_point(field_set:test.first.a)
}

// optional uint32 b = 2;
bool first::has_b() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void first::set_has_b() {
  _has_bits_[0] |= 0x00000002u;
}
void first::clear_has_b() {
  _has_bits_[0] &= ~0x00000002u;
}
void first::clear_b() {
  b_ = 0u;
  clear_has_b();
}
 ::google::protobuf::uint32 first::b() const {
  // @@protoc_insertion_point(field_get:test.first.b)
  return b_;
}
 void first::set_b(::google::protobuf::uint32 value) {
  set_has_b();
  b_ = value;
  // @@protoc_insertion_point(field_set:test.first.b)
}

// optional string c = 3;
bool first::has_c() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void first::set_has_c() {
  _has_bits_[0] |= 0x00000004u;
}
void first::clear_has_c() {
  _has_bits_[0] &= ~0x00000004u;
}
void first::clear_c() {
  c_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_c();
}
 const ::std::string& first::c() const {
  // @@protoc_insertion_point(field_get:test.first.c)
  return c_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void first::set_c(const ::std::string& value) {
  set_has_c();
  c_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:test.first.c)
}
 void first::set_c(const char* value) {
  set_has_c();
  c_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:test.first.c)
}
 void first::set_c(const char* value, size_t size) {
  set_has_c();
  c_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:test.first.c)
}
 ::std::string* first::mutable_c() {
  set_has_c();
  // @@protoc_insertion_point(field_mutable:test.first.c)
  return c_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* first::release_c() {
  // @@protoc_insertion_point(field_release:test.first.c)
  clear_has_c();
  return c_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void first::set_allocated_c(::std::string* c) {
  if (c != NULL) {
    set_has_c();
  } else {
    clear_has_c();
  }
  c_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), c);
  // @@protoc_insertion_point(field_set_allocated:test.first.c)
}

// repeated uint32 d = 4;
int first::d_size() const {
  return d_.size();
}
void first::clear_d() {
  d_.Clear();
}
 ::google::protobuf::uint32 first::d(int index) const {
  // @@protoc_insertion_point(field_get:test.first.d)
  return d_.Get(index);
}
 void first::set_d(int index, ::google::protobuf::uint32 value) {
  d_.Set(index, value);
  // @@protoc_insertion_point(field_set:test.first.d)
}
 void first::add_d(::google::protobuf::uint32 value) {
  d_.Add(value);
  // @@protoc_insertion_point(field_add:test.first.d)
}
 const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
first::d() const {
  // @@protoc_insertion_point(field_list:test.first.d)
  return d_;
}
 ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
first::mutable_d() {
  // @@protoc_insertion_point(field_mutable_list:test.first.d)
  return &d_;
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace test

// @@protoc_insertion_point(global_scope)
