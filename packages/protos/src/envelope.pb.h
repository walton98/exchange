// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: envelope.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_envelope_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_envelope_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "matcher.pb.h"
#include "oms.pb.h"
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_envelope_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_envelope_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_envelope_2eproto;
namespace envelope_proto {
class Envelope;
struct EnvelopeDefaultTypeInternal;
extern EnvelopeDefaultTypeInternal _Envelope_default_instance_;
}  // namespace envelope_proto
PROTOBUF_NAMESPACE_OPEN
template<> ::envelope_proto::Envelope* Arena::CreateMaybeMessage<::envelope_proto::Envelope>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace envelope_proto {

// ===================================================================

class Envelope final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:envelope_proto.Envelope) */ {
 public:
  inline Envelope() : Envelope(nullptr) {}
  ~Envelope() override;
  explicit PROTOBUF_CONSTEXPR Envelope(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Envelope(const Envelope& from);
  Envelope(Envelope&& from) noexcept
    : Envelope() {
    *this = ::std::move(from);
  }

  inline Envelope& operator=(const Envelope& from) {
    CopyFrom(from);
    return *this;
  }
  inline Envelope& operator=(Envelope&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Envelope& default_instance() {
    return *internal_default_instance();
  }
  enum PayloadCase {
    kMatcher = 2,
    kOms = 3,
    PAYLOAD_NOT_SET = 0,
  };

  static inline const Envelope* internal_default_instance() {
    return reinterpret_cast<const Envelope*>(
               &_Envelope_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Envelope& a, Envelope& b) {
    a.Swap(&b);
  }
  inline void Swap(Envelope* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Envelope* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Envelope* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Envelope>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Envelope& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Envelope& from) {
    Envelope::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Envelope* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "envelope_proto.Envelope";
  }
  protected:
  explicit Envelope(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSeqNumFieldNumber = 1,
    kMatcherFieldNumber = 2,
    kOmsFieldNumber = 3,
  };
  // uint64 seq_num = 1;
  void clear_seq_num();
  uint64_t seq_num() const;
  void set_seq_num(uint64_t value);
  private:
  uint64_t _internal_seq_num() const;
  void _internal_set_seq_num(uint64_t value);
  public:

  // .matcher_proto.Action matcher = 2;
  bool has_matcher() const;
  private:
  bool _internal_has_matcher() const;
  public:
  void clear_matcher();
  const ::matcher_proto::Action& matcher() const;
  PROTOBUF_NODISCARD ::matcher_proto::Action* release_matcher();
  ::matcher_proto::Action* mutable_matcher();
  void set_allocated_matcher(::matcher_proto::Action* matcher);
  private:
  const ::matcher_proto::Action& _internal_matcher() const;
  ::matcher_proto::Action* _internal_mutable_matcher();
  public:
  void unsafe_arena_set_allocated_matcher(
      ::matcher_proto::Action* matcher);
  ::matcher_proto::Action* unsafe_arena_release_matcher();

  // .oms_proto.Action oms = 3;
  bool has_oms() const;
  private:
  bool _internal_has_oms() const;
  public:
  void clear_oms();
  const ::oms_proto::Action& oms() const;
  PROTOBUF_NODISCARD ::oms_proto::Action* release_oms();
  ::oms_proto::Action* mutable_oms();
  void set_allocated_oms(::oms_proto::Action* oms);
  private:
  const ::oms_proto::Action& _internal_oms() const;
  ::oms_proto::Action* _internal_mutable_oms();
  public:
  void unsafe_arena_set_allocated_oms(
      ::oms_proto::Action* oms);
  ::oms_proto::Action* unsafe_arena_release_oms();

  void clear_payload();
  PayloadCase payload_case() const;
  // @@protoc_insertion_point(class_scope:envelope_proto.Envelope)
 private:
  class _Internal;
  void set_has_matcher();
  void set_has_oms();

  inline bool has_payload() const;
  inline void clear_has_payload();

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    uint64_t seq_num_;
    union PayloadUnion {
      constexpr PayloadUnion() : _constinit_{} {}
        ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized _constinit_;
      ::matcher_proto::Action* matcher_;
      ::oms_proto::Action* oms_;
    } payload_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    uint32_t _oneof_case_[1];

  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_envelope_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Envelope

// uint64 seq_num = 1;
inline void Envelope::clear_seq_num() {
  _impl_.seq_num_ = uint64_t{0u};
}
inline uint64_t Envelope::_internal_seq_num() const {
  return _impl_.seq_num_;
}
inline uint64_t Envelope::seq_num() const {
  // @@protoc_insertion_point(field_get:envelope_proto.Envelope.seq_num)
  return _internal_seq_num();
}
inline void Envelope::_internal_set_seq_num(uint64_t value) {
  
  _impl_.seq_num_ = value;
}
inline void Envelope::set_seq_num(uint64_t value) {
  _internal_set_seq_num(value);
  // @@protoc_insertion_point(field_set:envelope_proto.Envelope.seq_num)
}

// .matcher_proto.Action matcher = 2;
inline bool Envelope::_internal_has_matcher() const {
  return payload_case() == kMatcher;
}
inline bool Envelope::has_matcher() const {
  return _internal_has_matcher();
}
inline void Envelope::set_has_matcher() {
  _impl_._oneof_case_[0] = kMatcher;
}
inline ::matcher_proto::Action* Envelope::release_matcher() {
  // @@protoc_insertion_point(field_release:envelope_proto.Envelope.matcher)
  if (_internal_has_matcher()) {
    clear_has_payload();
    ::matcher_proto::Action* temp = _impl_.payload_.matcher_;
    if (GetArenaForAllocation() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    _impl_.payload_.matcher_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::matcher_proto::Action& Envelope::_internal_matcher() const {
  return _internal_has_matcher()
      ? *_impl_.payload_.matcher_
      : reinterpret_cast< ::matcher_proto::Action&>(::matcher_proto::_Action_default_instance_);
}
inline const ::matcher_proto::Action& Envelope::matcher() const {
  // @@protoc_insertion_point(field_get:envelope_proto.Envelope.matcher)
  return _internal_matcher();
}
inline ::matcher_proto::Action* Envelope::unsafe_arena_release_matcher() {
  // @@protoc_insertion_point(field_unsafe_arena_release:envelope_proto.Envelope.matcher)
  if (_internal_has_matcher()) {
    clear_has_payload();
    ::matcher_proto::Action* temp = _impl_.payload_.matcher_;
    _impl_.payload_.matcher_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void Envelope::unsafe_arena_set_allocated_matcher(::matcher_proto::Action* matcher) {
  clear_payload();
  if (matcher) {
    set_has_matcher();
    _impl_.payload_.matcher_ = matcher;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:envelope_proto.Envelope.matcher)
}
inline ::matcher_proto::Action* Envelope::_internal_mutable_matcher() {
  if (!_internal_has_matcher()) {
    clear_payload();
    set_has_matcher();
    _impl_.payload_.matcher_ = CreateMaybeMessage< ::matcher_proto::Action >(GetArenaForAllocation());
  }
  return _impl_.payload_.matcher_;
}
inline ::matcher_proto::Action* Envelope::mutable_matcher() {
  ::matcher_proto::Action* _msg = _internal_mutable_matcher();
  // @@protoc_insertion_point(field_mutable:envelope_proto.Envelope.matcher)
  return _msg;
}

// .oms_proto.Action oms = 3;
inline bool Envelope::_internal_has_oms() const {
  return payload_case() == kOms;
}
inline bool Envelope::has_oms() const {
  return _internal_has_oms();
}
inline void Envelope::set_has_oms() {
  _impl_._oneof_case_[0] = kOms;
}
inline ::oms_proto::Action* Envelope::release_oms() {
  // @@protoc_insertion_point(field_release:envelope_proto.Envelope.oms)
  if (_internal_has_oms()) {
    clear_has_payload();
    ::oms_proto::Action* temp = _impl_.payload_.oms_;
    if (GetArenaForAllocation() != nullptr) {
      temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
    }
    _impl_.payload_.oms_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline const ::oms_proto::Action& Envelope::_internal_oms() const {
  return _internal_has_oms()
      ? *_impl_.payload_.oms_
      : reinterpret_cast< ::oms_proto::Action&>(::oms_proto::_Action_default_instance_);
}
inline const ::oms_proto::Action& Envelope::oms() const {
  // @@protoc_insertion_point(field_get:envelope_proto.Envelope.oms)
  return _internal_oms();
}
inline ::oms_proto::Action* Envelope::unsafe_arena_release_oms() {
  // @@protoc_insertion_point(field_unsafe_arena_release:envelope_proto.Envelope.oms)
  if (_internal_has_oms()) {
    clear_has_payload();
    ::oms_proto::Action* temp = _impl_.payload_.oms_;
    _impl_.payload_.oms_ = nullptr;
    return temp;
  } else {
    return nullptr;
  }
}
inline void Envelope::unsafe_arena_set_allocated_oms(::oms_proto::Action* oms) {
  clear_payload();
  if (oms) {
    set_has_oms();
    _impl_.payload_.oms_ = oms;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:envelope_proto.Envelope.oms)
}
inline ::oms_proto::Action* Envelope::_internal_mutable_oms() {
  if (!_internal_has_oms()) {
    clear_payload();
    set_has_oms();
    _impl_.payload_.oms_ = CreateMaybeMessage< ::oms_proto::Action >(GetArenaForAllocation());
  }
  return _impl_.payload_.oms_;
}
inline ::oms_proto::Action* Envelope::mutable_oms() {
  ::oms_proto::Action* _msg = _internal_mutable_oms();
  // @@protoc_insertion_point(field_mutable:envelope_proto.Envelope.oms)
  return _msg;
}

inline bool Envelope::has_payload() const {
  return payload_case() != PAYLOAD_NOT_SET;
}
inline void Envelope::clear_has_payload() {
  _impl_._oneof_case_[0] = PAYLOAD_NOT_SET;
}
inline Envelope::PayloadCase Envelope::payload_case() const {
  return Envelope::PayloadCase(_impl_._oneof_case_[0]);
}
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace envelope_proto

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_envelope_2eproto
