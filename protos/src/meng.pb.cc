// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: meng.proto

#include "meng.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace meng_proto {
PROTOBUF_CONSTEXPR Book::Book(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.id_)*/int64_t{0}} {}
struct BookDefaultTypeInternal {
  PROTOBUF_CONSTEXPR BookDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~BookDefaultTypeInternal() {}
  union {
    Book _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 BookDefaultTypeInternal _Book_default_instance_;
}  // namespace meng_proto
static ::_pb::Metadata file_level_metadata_meng_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_meng_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_meng_2eproto = nullptr;

const uint32_t TableStruct_meng_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::meng_proto::Book, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::meng_proto::Book, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::meng_proto::Book, _impl_.id_),
  0,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, -1, sizeof(::meng_proto::Book)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::meng_proto::_Book_default_instance_._instance,
};

const char descriptor_table_protodef_meng_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\nmeng.proto\022\nmeng_proto\"\036\n\004Book\022\017\n\002id\030\001"
  " \001(\003H\000\210\001\001B\005\n\003_idb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_meng_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_meng_2eproto = {
    false, false, 64, descriptor_table_protodef_meng_2eproto,
    "meng.proto",
    &descriptor_table_meng_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_meng_2eproto::offsets,
    file_level_metadata_meng_2eproto, file_level_enum_descriptors_meng_2eproto,
    file_level_service_descriptors_meng_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_meng_2eproto_getter() {
  return &descriptor_table_meng_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_meng_2eproto(&descriptor_table_meng_2eproto);
namespace meng_proto {

// ===================================================================

class Book::_Internal {
 public:
  using HasBits = decltype(std::declval<Book>()._impl_._has_bits_);
  static void set_has_id(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

Book::Book(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:meng_proto.Book)
}
Book::Book(const Book& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Book* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.id_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.id_ = from._impl_.id_;
  // @@protoc_insertion_point(copy_constructor:meng_proto.Book)
}

inline void Book::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.id_){int64_t{0}}
  };
}

Book::~Book() {
  // @@protoc_insertion_point(destructor:meng_proto.Book)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Book::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Book::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Book::Clear() {
// @@protoc_insertion_point(message_clear_start:meng_proto.Book)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.id_ = int64_t{0};
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Book::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional int64 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _Internal::set_has_id(&has_bits);
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Book::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:meng_proto.Book)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // optional int64 id = 1;
  if (_internal_has_id()) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt64ToArray(1, this->_internal_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:meng_proto.Book)
  return target;
}

size_t Book::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:meng_proto.Book)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional int64 id = 1;
  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += ::_pbi::WireFormatLite::Int64SizePlusOne(this->_internal_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Book::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Book::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Book::GetClassData() const { return &_class_data_; }


void Book::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Book*>(&to_msg);
  auto& from = static_cast<const Book&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:meng_proto.Book)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_id()) {
    _this->_internal_set_id(from._internal_id());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Book::CopyFrom(const Book& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:meng_proto.Book)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Book::IsInitialized() const {
  return true;
}

void Book::InternalSwap(Book* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  swap(_impl_.id_, other->_impl_.id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Book::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_meng_2eproto_getter, &descriptor_table_meng_2eproto_once,
      file_level_metadata_meng_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace meng_proto
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::meng_proto::Book*
Arena::CreateMaybeMessage< ::meng_proto::Book >(Arena* arena) {
  return Arena::CreateMessageInternal< ::meng_proto::Book >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
