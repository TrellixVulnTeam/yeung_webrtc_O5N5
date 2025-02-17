/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 *
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 *
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 *
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */
/* ====================================================================
 * Copyright (c) 1998-2007 The OpenSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit. (http://www.openssl.org/)"
 *
 * 4. The names "OpenSSL Toolkit" and "OpenSSL Project" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    openssl-core@openssl.org.
 *
 * 5. Products derived from this software may not be called "OpenSSL"
 *    nor may "OpenSSL" appear in their names without prior written
 *    permission of the OpenSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the OpenSSL Project
 *    for use in the OpenSSL Toolkit (http://www.openssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE OpenSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE OpenSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This product includes cryptographic software written by Eric Young
 * (eay@cryptsoft.com).  This product includes software written by Tim
 * Hudson (tjh@cryptsoft.com).
 *
 */
/* ====================================================================
 * Copyright 2002 Sun Microsystems, Inc. ALL RIGHTS RESERVED.
 * ECC cipher suite support in OpenSSL originally developed by
 * SUN MICROSYSTEMS, INC., and contributed to the OpenSSL project.
 */
/* ====================================================================
 * Copyright 2005 Nokia. All rights reserved.
 *
 * The portions of the attached software ("Contribution") is developed by
 * Nokia Corporation and is licensed pursuant to the OpenSSL open source
 * license.
 *
 * The Contribution, originally written by Mika Kousa and Pasi Eronen of
 * Nokia Corporation, consists of the "PSK" (Pre-Shared Key) ciphersuites
 * support (see RFC 4279) to OpenSSL.
 *
 * No patent licenses or other rights except those expressly stated in
 * the OpenSSL open source license shall be deemed granted or received
 * expressly, by implication, estoppel, or otherwise.
 *
 * No assurances are provided by Nokia that the Contribution does not
 * infringe the patent or other intellectual property rights of any third
 * party or that the license provides you with all the necessary rights
 * to make use of the Contribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. IN
 * ADDITION TO THE DISCLAIMERS INCLUDED IN THE LICENSE, NOKIA
 * SPECIFICALLY DISCLAIMS ANY LIABILITY FOR CLAIMS BROUGHT BY YOU OR ANY
 * OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS OR
 * OTHERWISE.
 */

#ifndef OPENSSL_HEADER_SSL_INTERNAL_H
#define OPENSSL_HEADER_SSL_INTERNAL_H

#include <openssl/base.h>

#include <stdlib.h>

#include <new>
#include <type_traits>
#include <utility>

#include <openssl/aead.h>
#include <openssl/err.h>
#include <openssl/mem.h>
#include <openssl/ssl.h>
#include <openssl/stack.h>


#if defined(OPENSSL_WINDOWS)
/* Windows defines struct timeval in winsock2.h. */
OPENSSL_MSVC_PRAGMA(warning(push, 3))
#include <winsock2.h>
OPENSSL_MSVC_PRAGMA(warning(pop))
#else
#include <sys/time.h>
#endif


typedef struct cert_st CERT;

namespace bssl {

struct SSL_HANDSHAKE;

/* C++ utilities. */

/* New behaves like |new| but uses |OPENSSL_malloc| for memory allocation. It
 * returns nullptr on allocation error. It only implements single-object
 * allocation and not new T[n].
 *
 * Note: unlike |new|, this does not support non-public constructors. */
template <typename T, typename... Args>
T *New(Args &&... args) {
  void *t = OPENSSL_malloc(sizeof(T));
  if (t == nullptr) {
    OPENSSL_PUT_ERROR(SSL, ERR_R_MALLOC_FAILURE);
    return nullptr;
  }
  return new (t) T(std::forward<Args>(args)...);
}

/* Delete behaves like |delete| but uses |OPENSSL_free| to release memory.
 *
 * Note: unlike |delete| this does not support non-public destructors. */
template <typename T>
void Delete(T *t) {
  if (t != nullptr) {
    t->~T();
    OPENSSL_free(t);
  }
}

/* All types with kAllowUniquePtr set may be used with UniquePtr. Other types
 * may be C structs which require a |BORINGSSL_MAKE_DELETER| registration. */
namespace internal {
template <typename T>
struct DeleterImpl<T, typename std::enable_if<T::kAllowUniquePtr>::type> {
  static void Free(T *t) { Delete(t); }
};
}

/* MakeUnique behaves like |std::make_unique| but returns nullptr on allocation
 * error. */
template <typename T, typename... Args>
UniquePtr<T> MakeUnique(Args &&... args) {
  return UniquePtr<T>(New<T>(std::forward<Args>(args)...));
}

#if defined(BORINGSSL_ALLOW_CXX_RUNTIME)
#define HAS_VIRTUAL_DESTRUCTOR
#define PURE_VIRTUAL = 0
#else
/* HAS_VIRTUAL_DESTRUCTOR should be declared in any base clas ~s which defines a
 * virtual destructor. This avoids a dependency on |_ZdlPv| and prevents the
 * class from being used with |delete|. */
#define HAS_VIRTUAL_DESTRUCTOR \
  void operator delete(void *) { abort(); }

/* PURE_VIRTUAL should be used instead of = 0 when defining pure-virtual
 * functions. This avoids a dependency on |__cxa_pure_virtual| but loses
 * compile-time checking. */
#define PURE_VIRTUAL { abort(); }
#endif


/* Protocol versions.
 *
 * Due to DTLS's historical wire version differences and to support multiple
 * variants of the same protocol during development, we maintain two notions of
 * version.
 *
 * The "version" or "wire version" is the actual 16-bit value that appears on
 * the wire. It uniquely identifies a version and is also used at API
 * boundaries. The set of supported versions differs between TLS and DTLS. Wire
 * versions are opaque values and may not be compared numerically.
 *
 * The "protocol version" identifies the high-level handshake variant being
 * used. DTLS versions map to the corresponding TLS versions. Draft TLS 1.3
 * variants all map to TLS 1.3. Protocol versions are sequential and may be
 * compared numerically. */

/* ssl_protocol_version_from_wire sets |*out| to the protocol version
 * corresponding to wire version |version| and returns one. If |version| is not
 * a valid TLS or DTLS version, it returns zero.
 *
 * Note this simultaneously handles both DTLS and TLS. Use one of the
 * higher-level functions below for most operations. */
int ssl_protocol_version_from_wire(uint16_t *out, uint16_t version);

/* ssl_get_version_range sets |*out_min_version| and |*out_max_version| to the
 * minimum and maximum enabled protocol versions, respectively. */
int ssl_get_version_range(const SSL *ssl, uint16_t *out_min_version,
                          uint16_t *out_max_version);

/* ssl_supports_version returns one if |hs| supports |version| and zero
 * otherwise. */
int ssl_supports_version(SSL_HANDSHAKE *hs, uint16_t version);

/* ssl_add_supported_versions writes the supported versions of |hs| to |cbb|, in
 * decreasing preference order. */
int ssl_add_supported_versions(SSL_HANDSHAKE *hs, CBB *cbb);

/* ssl_negotiate_version negotiates a common version based on |hs|'s preferences
 * and the peer preference list in |peer_versions|. On success, it returns one
 * and sets |*out_version| to the selected version. Otherwise, it returns zero
 * and sets |*out_alert| to an alert to send. */
int ssl_negotiate_version(SSL_HANDSHAKE *hs, uint8_t *out_alert,
                          uint16_t *out_version, const CBS *peer_versions);

/* ssl3_protocol_version returns |ssl|'s protocol version. It is an error to
 * call this function before the version is determined. */
uint16_t ssl3_protocol_version(const SSL *ssl);


/* Cipher suites. */

/* Bits for |algorithm_mkey| (key exchange algorithm). */
#define SSL_kRSA 0x00000001u
#define SSL_kECDHE 0x00000002u
/* SSL_kPSK is only set for plain PSK, not ECDHE_PSK. */
#define SSL_kPSK 0x00000004u
#define SSL_kGENERIC 0x00000008u

/* Bits for |algorithm_auth| (server authentication). */
#define SSL_aRSA 0x00000001u
#define SSL_aECDSA 0x00000002u
/* SSL_aPSK is set for both PSK and ECDHE_PSK. */
#define SSL_aPSK 0x00000004u
#define SSL_aGENERIC 0x00000008u

#define SSL_aCERT (SSL_aRSA | SSL_aECDSA)

/* Bits for |algorithm_enc| (symmetric encryption). */
#define SSL_3DES                 0x00000001u
#define SSL_AES128               0x00000002u
#define SSL_AES256               0x00000004u
#define SSL_AES128GCM            0x00000008u
#define SSL_AES256GCM            0x00000010u
#define SSL_eNULL                0x00000020u
#define SSL_CHACHA20POLY1305     0x00000040u

#define SSL_AES (SSL_AES128 | SSL_AES256 | SSL_AES128GCM | SSL_AES256GCM)

/* Bits for |algorithm_mac| (symmetric authentication). */
#define SSL_SHA1 0x00000001u
#define SSL_SHA256 0x00000002u
#define SSL_SHA384 0x00000004u
/* SSL_AEAD is set for all AEADs. */
#define SSL_AEAD 0x00000008u

/* Bits for |algorithm_prf| (handshake digest). */
#define SSL_HANDSHAKE_MAC_DEFAULT 0x1
#define SSL_HANDSHAKE_MAC_SHA256 0x2
#define SSL_HANDSHAKE_MAC_SHA384 0x4

/* SSL_MAX_DIGEST is the number of digest types which exist. When adding a new
 * one, update the table in ssl_cipher.c. */
#define SSL_MAX_DIGEST 4

/* ssl_cipher_get_evp_aead sets |*out_aead| to point to the correct EVP_AEAD
 * object for |cipher| protocol version |version|. It sets |*out_mac_secret_len|
 * and |*out_fixed_iv_len| to the MAC key length and fixed IV length,
 * respectively. The MAC key length is zero except for legacy block and stream
 * ciphers. It returns 1 on success and 0 on error. */
int ssl_cipher_get_evp_aead(const EVP_AEAD **out_aead,
                            size_t *out_mac_secret_len,
                            size_t *out_fixed_iv_len, const SSL_CIPHER *cipher,
                            uint16_t version, int is_dtls);

/* ssl_get_handshake_digest returns the |EVP_MD| corresponding to |version| and
 * |cipher|. */
const EVP_MD *ssl_get_handshake_digest(uint16_t version,
                                       const SSL_CIPHER *cipher);

/* ssl_create_cipher_list evaluates |rule_str| according to the ciphers in
 * |ssl_method|. It sets |*out_cipher_list| to a newly-allocated
 * |ssl_cipher_preference_list_st| containing the result. It returns 1 on
 * success and 0 on failure. If |strict| is true, nonsense will be rejected. If
 * false, nonsense will be silently ignored. An empty result is considered an
 * error regardless of |strict|. */
int ssl_create_cipher_list(
    const SSL_PROTOCOL_METHOD *ssl_method,
    struct ssl_cipher_preference_list_st **out_cipher_list,
    const char *rule_str, int strict);

/* ssl_cipher_get_value returns the cipher suite id of |cipher|. */
uint16_t ssl_cipher_get_value(const SSL_CIPHER *cipher);

/* ssl_cipher_auth_mask_for_key returns the mask of cipher |algorithm_auth|
 * values suitable for use with |key| in TLS 1.2 and below. */
uint32_t ssl_cipher_auth_mask_for_key(const EVP_PKEY *key);

/* ssl_cipher_uses_certificate_auth returns one if |cipher| authenticates the
 * server and, optionally, the client with a certificate. Otherwise it returns
 * zero. */
int ssl_cipher_uses_certificate_auth(const SSL_CIPHER *cipher);

/* ssl_cipher_requires_server_key_exchange returns 1 if |cipher| requires a
 * ServerKeyExchange message. Otherwise it returns 0.
 *
 * This function may return zero while still allowing |cipher| an optional
 * ServerKeyExchange. This is the case for plain PSK ciphers. */
int ssl_cipher_requires_server_key_exchange(const SSL_CIPHER *cipher);

/* ssl_cipher_get_record_split_len, for TLS 1.0 CBC mode ciphers, returns the
 * length of an encrypted 1-byte record, for use in record-splitting. Otherwise
 * it returns zero. */
size_t ssl_cipher_get_record_split_len(const SSL_CIPHER *cipher);


/* Transcript layer. */

/* SSLTranscript maintains the handshake transcript as a combination of a
 * buffer and running hash. */
class SSLTranscript {
 public:
  SSLTranscript();
  ~SSLTranscript();

  /* Init initializes the handshake transcript. If called on an existing
   * transcript, it resets the transcript and hash. It returns true on success
   * and false on failure. */
  bool Init();

  /* InitHash initializes the handshake hash based on the PRF and contents of
   * the handshake transcript. Subsequent calls to |Update| will update the
   * rolling hash. It returns one on success and zero on failure. It is an error
   * to call this function after the handshake buffer is released. */
  bool InitHash(uint16_t version, const SSL_CIPHER *cipher);

  const uint8_t *buffer_data() const {
    return reinterpret_cast<const uint8_t *>(buffer_->data);
  }
  size_t buffer_len() const { return buffer_->length; }

  /* FreeBuffer releases the handshake buffer. Subsequent calls to
   * |Update| will not update the handshake buffer. */
  void FreeBuffer();

  /* DigestLen returns the length of the PRF hash. */
  size_t DigestLen() const;

  /* Digest returns the PRF hash. For TLS 1.1 and below, this is
   * |EVP_md5_sha1|. */
  const EVP_MD *Digest() const;

  /* Update adds |in| to the handshake buffer and handshake hash, whichever is
   * enabled. It returns true on success and false on failure. */
  bool Update(const uint8_t *in, size_t in_len);

  /* GetHash writes the handshake hash to |out| which must have room for at
   * least |DigestLen| bytes. On success, it returns true and sets |*out_len| to
   * the number of bytes written. Otherwise, it returns false. */
  bool GetHash(uint8_t *out, size_t *out_len);

  /* GetSSL3CertVerifyHash writes the SSL 3.0 CertificateVerify hash into the
   * bytes pointed to by |out| and writes the number of bytes to
   * |*out_len|. |out| must have room for |EVP_MAX_MD_SIZE| bytes. It returns
   * one on success and zero on failure. */
  bool GetSSL3CertVerifyHash(uint8_t *out, size_t *out_len,
                             const SSL_SESSION *session,
                             uint16_t signature_algorithm);

  /* GetFinishedMAC computes the MAC for the Finished message into the bytes
   * pointed by |out| and writes the number of bytes to |*out_len|. |out| must
   * have room for |EVP_MAX_MD_SIZE| bytes. It returns true on success and false
   * on failure. */
  bool GetFinishedMAC(uint8_t *out, size_t *out_len, const SSL_SESSION *session,
                      bool from_server, uint16_t version);

 private:
  /* buffer_, if non-null, contains the handshake transcript. */
  UniquePtr<BUF_MEM> buffer_;
  /* hash, if initialized with an |EVP_MD|, maintains the handshake hash. For
   * TLS 1.1 and below, it is the SHA-1 half. */
  ScopedEVP_MD_CTX hash_;
  /* md5, if initialized with an |EVP_MD|, maintains the MD5 half of the
   * handshake hash for TLS 1.1 and below. */
  ScopedEVP_MD_CTX md5_;
};

/* tls1_prf computes the PRF function for |ssl|. It writes |out_len| bytes to
 * |out|, using |secret| as the secret and |label| as the label. |seed1| and
 * |seed2| are concatenated to form the seed parameter. It returns one on
 * success and zero on failure. */
int tls1_prf(const EVP_MD *digest, uint8_t *out, size_t out_len,
             const uint8_t *secret, size_t secret_len, const char *label,
             size_t label_len, const uint8_t *seed1, size_t seed1_len,
             const uint8_t *seed2, size_t seed2_len);


/* Encryption layer. */

/* SSLAEADContext contains information about an AEAD that is being used to
 * encrypt an SSL connection. */
class SSLAEADContext {
 public:
  SSLAEADContext(uint16_t version, const SSL_CIPHER *cipher);
  ~SSLAEADContext();
  static constexpr bool kAllowUniquePtr = true;

  SSLAEADContext(const SSLAEADContext &&) = delete;
  SSLAEADContext &operator=(const SSLAEADContext &&) = delete;

  /* CreateNullCipher creates an |SSLAEADContext| for the null cipher. */
  static UniquePtr<SSLAEADContext> CreateNullCipher();

  /* Create creates an |SSLAEADContext| using the supplied key material. It
   * returns nullptr on error. Only one of |Open| or |Seal| may be used with the
   * resulting object, depending on |direction|. |version| is the normalized
   * protocol version, so DTLS 1.0 is represented as 0x0301, not 0xffef. */
  static UniquePtr<SSLAEADContext> Create(
      enum evp_aead_direction_t direction, uint16_t version, int is_dtls,
      const SSL_CIPHER *cipher, const uint8_t *enc_key, size_t enc_key_len,
      const uint8_t *mac_key, size_t mac_key_len, const uint8_t *fixed_iv,
      size_t fixed_iv_len);

  uint16_t version() const { return version_; }
  const SSL_CIPHER *cipher() const { return cipher_; }

  /* is_null_cipher returns true if this is the null cipher. */
  bool is_null_cipher() const { return !cipher_; }

  /* ExplicitNonceLen returns the length of the explicit nonce. */
  size_t ExplicitNonceLen() const;

  /* MaxOverhead returns the maximum overhead of calling |Seal|. */
  size_t MaxOverhead() const;

  /* SuffixLen calculates the suffix length written by |SealScatter| and writes
   * it to |*out_suffix_len|. It returns true on success and false on error.
   * |in_len| and |extra_in_len| should equal the argument of the same names
   * passed to |SealScatter|. */
  bool SuffixLen(size_t *out_suffix_len, size_t in_len,
                 size_t extra_in_len) const;

  /* Open authenticates and decrypts |in_len| bytes from |in| in-place. On
   * success, it sets |*out| to the plaintext in |in| and returns true.
   * Otherwise, it returns false. The output will always be |ExplicitNonceLen|
   * bytes ahead of |in|. */
  bool Open(CBS *out, uint8_t type, uint16_t wire_version,
            const uint8_t seqnum[8], uint8_t *in, size_t in_len);

  /* Seal encrypts and authenticates |in_len| bytes from |in| and writes the
   * result to |out|. It returns true on success and false on error.
   *
   * If |in| and |out| alias then |out| + |ExplicitNonceLen| must be == |in|. */
  bool Seal(uint8_t *out, size_t *out_len, size_t max_out, uint8_t type,
            uint16_t wire_version, const uint8_t seqnum[8], const uint8_t *in,
            size_t in_len);

  /* SealScatter encrypts and authenticates |in_len| bytes from |in| and splits
   * the result between |out_prefix|, |out| and |out_suffix|. It returns one on
   * success and zero on error.
   *
   * On successful return, exactly |ExplicitNonceLen| bytes are written to
   * |out_prefix|, |in_len| bytes to |out|, and |SuffixLen| bytes to
   * |out_suffix|.
   *
   * |extra_in| may point to an additional plaintext buffer. If present,
   * |extra_in_len| additional bytes are encrypted and authenticated, and the
   * ciphertext is written to the beginning of |out_suffix|. |SuffixLen| should
   * be used to size |out_suffix| accordingly.
   *
   * If |in| and |out| alias then |out| must be == |in|. Other arguments may not
   * alias anything. */
  bool SealScatter(uint8_t *out_prefix, uint8_t *out, uint8_t *out_suffix,
                   uint8_t type, uint16_t wire_version, const uint8_t seqnum[8],
                   const uint8_t *in, size_t in_len, const uint8_t *extra_in,
                   size_t extra_in_len);

  bool GetIV(const uint8_t **out_iv, size_t *out_iv_len) const;

 private:
  /* GetAdditionalData writes the additional data into |out| and returns the
   * number of bytes written. */
  size_t GetAdditionalData(uint8_t out[13], uint8_t type, uint16_t wire_version,
                           const uint8_t seqnum[8], size_t plaintext_len);

  const SSL_CIPHER *cipher_;
  ScopedEVP_AEAD_CTX ctx_;
  /* fixed_nonce_ contains any bytes of the nonce that are fixed for all
   * records. */
  uint8_t fixed_nonce_[12];
  uint8_t fixed_nonce_len_ = 0, variable_nonce_len_ = 0;
  /* version_ is the protocol version that should be used with this AEAD. */
  uint16_t version_;
  /* variable_nonce_included_in_record_ is true if the variable nonce
   * for a record is included as a prefix before the ciphertext. */
  bool variable_nonce_included_in_record_ : 1;
  /* random_variable_nonce_ is true if the variable nonce is
   * randomly generated, rather than derived from the sequence
   * number. */
  bool random_variable_nonce_ : 1;
  /* omit_length_in_ad_ is true if the length should be omitted in the
   * AEAD's ad parameter. */
  bool omit_length_in_ad_ : 1;
  /* omit_version_in_ad_ is true if the version should be omitted
   * in the AEAD's ad parameter. */
  bool omit_version_in_ad_ : 1;
  /* omit_ad_ is true if the AEAD's ad parameter should be omitted. */
  bool omit_ad_ : 1;
  /* xor_fixed_nonce_ is true if the fixed nonce should be XOR'd into the
   * variable nonce rather than prepended. */
  bool xor_fixed_nonce_ : 1;
};


/* DTLS replay bitmap. */

/* DTLS1_BITMAP maintains a sliding window of 64 sequence numbers to detect
 * replayed packets. It should be initialized by zeroing every field. */
struct DTLS1_BITMAP {
  /* map is a bit mask of the last 64 sequence numbers. Bit
   * |1<<i| corresponds to |max_seq_num - i|. */
  uint64_t map;
  /* max_seq_num is the largest sequence number seen so far as a 64-bit
   * integer. */
  uint64_t max_seq_num;
};


/* Record layer. */

/* ssl_record_sequence_update increments the sequence number in |seq|. It
 * returns one on success and zero on wraparound. */
int ssl_record_sequence_update(uint8_t *seq, size_t seq_len);

/* ssl_record_prefix_len returns the length of the prefix before the ciphertext
 * of a record for |ssl|.
 *
 * TODO(davidben): Expose this as part of public API once the high-level
 * buffer-free APIs are available. */
size_t ssl_record_prefix_len(const SSL *ssl);

enum ssl_open_record_t {
  ssl_open_record_success,
  ssl_open_record_discard,
  ssl_open_record_partial,
  ssl_open_record_close_notify,
  ssl_open_record_fatal_alert,
  ssl_open_record_error,
};

/* tls_open_record decrypts a record from |in| in-place.
 *
 * If the input did not contain a complete record, it returns
 * |ssl_open_record_partial|. It sets |*out_consumed| to the total number of
 * bytes necessary. It is guaranteed that a successful call to |tls_open_record|
 * will consume at least that many bytes.
 *
 * Otherwise, it sets |*out_consumed| to the number of bytes of input
 * consumed. Note that input may be consumed on all return codes if a record was
 * decrypted.
 *
 * On success, it returns |ssl_open_record_success|. It sets |*out_type| to the
 * record type and |*out| to the record body in |in|. Note that |*out| may be
 * empty.
 *
 * If a record was successfully processed but should be discarded, it returns
 * |ssl_open_record_discard|.
 *
 * If a record was successfully processed but is a close_notify or fatal alert,
 * it returns |ssl_open_record_close_notify| or |ssl_open_record_fatal_alert|.
 *
 * On failure, it returns |ssl_open_record_error| and sets |*out_alert| to an
 * alert to emit. */
enum ssl_open_record_t tls_open_record(SSL *ssl, uint8_t *out_type, CBS *out,
                                       size_t *out_consumed, uint8_t *out_alert,
                                       uint8_t *in, size_t in_len);

/* dtls_open_record implements |tls_open_record| for DTLS. It never returns
 * |ssl_open_record_partial| but otherwise behaves analogously. */
enum ssl_open_record_t dtls_open_record(SSL *ssl, uint8_t *out_type, CBS *out,
                                        size_t *out_consumed,
                                        uint8_t *out_alert, uint8_t *in,
                                        size_t in_len);

/* ssl_seal_align_prefix_len returns the length of the prefix before the start
 * of the bulk of the ciphertext when sealing a record with |ssl|. Callers may
 * use this to align buffers.
 *
 * Note when TLS 1.0 CBC record-splitting is enabled, this includes the one byte
 * record and is the offset into second record's ciphertext. Thus sealing a
 * small record may result in a smaller output than this value.
 *
 * TODO(davidben): Is this alignment valuable? Record-splitting makes this a
 * mess. */
size_t ssl_seal_align_prefix_len(const SSL *ssl);

/* tls_seal_record seals a new record of type |type| and body |in| and writes it
 * to |out|. At most |max_out| bytes will be written. It returns one on success
 * and zero on error. If enabled, |tls_seal_record| implements TLS 1.0 CBC 1/n-1
 * record splitting and may write two records concatenated.
 *
 * For a large record, the bulk of the ciphertext will begin
 * |ssl_seal_align_prefix_len| bytes into out. Aligning |out| appropriately may
 * improve performance. It writes at most |in_len| + |SSL_max_seal_overhead|
 * bytes to |out|.
 *
 * |in| and |out| may not alias. */
int tls_seal_record(SSL *ssl, uint8_t *out, size_t *out_len, size_t max_out,
                    uint8_t type, const uint8_t *in, size_t in_len);

enum dtls1_use_epoch_t {
  dtls1_use_previous_epoch,
  dtls1_use_current_epoch,
};

/* dtls_max_seal_overhead returns the maximum overhead, in bytes, of sealing a
 * record. */
size_t dtls_max_seal_overhead(const SSL *ssl, enum dtls1_use_epoch_t use_epoch);

/* dtls_seal_prefix_len returns the number of bytes of prefix to reserve in
 * front of the plaintext when sealing a record in-place. */
size_t dtls_seal_prefix_len(const SSL *ssl, enum dtls1_use_epoch_t use_epoch);

/* dtls_seal_record implements |tls_seal_record| for DTLS. |use_epoch| selects
 * which epoch's cipher state to use. Unlike |tls_seal_record|, |in| and |out|
 * may alias but, if they do, |in| must be exactly |dtls_seal_prefix_len| bytes
 * ahead of |out|. */
int dtls_seal_record(SSL *ssl, uint8_t *out, size_t *out_len, size_t max_out,
                     uint8_t type, const uint8_t *in, size_t in_len,
                     enum dtls1_use_epoch_t use_epoch);

/* ssl_process_alert processes |in| as an alert and updates |ssl|'s shutdown
 * state. It returns one of |ssl_open_record_discard|, |ssl_open_record_error|,
 * |ssl_open_record_close_notify|, or |ssl_open_record_fatal_alert| as
 * appropriate. */
enum ssl_open_record_t ssl_process_alert(SSL *ssl, uint8_t *out_alert,
                                         const uint8_t *in, size_t in_len);


/* Private key operations. */

/* ssl_has_private_key returns one if |ssl| has a private key
 * configured and zero otherwise. */
int ssl_has_private_key(const SSL *ssl);

/* ssl_private_key_* perform the corresponding operation on
 * |SSL_PRIVATE_KEY_METHOD|. If there is a custom private key configured, they
 * call the corresponding function or |complete| depending on whether there is a
 * pending operation. Otherwise, they implement the operation with
 * |EVP_PKEY|. */

enum ssl_private_key_result_t ssl_private_key_sign(
    SSL_HANDSHAKE *hs, uint8_t *out, size_t *out_len, size_t max_out,
    uint16_t sigalg, const uint8_t *in, size_t in_len);

enum ssl_private_key_result_t ssl_private_key_decrypt(
    SSL_HANDSHAKE *hs, uint8_t *out, size_t *out_len, size_t max_out,
    const uint8_t *in, size_t in_len);

/* ssl_private_key_supports_signature_algorithm returns one if |hs|'s private
 * key supports |sigalg| and zero otherwise. */
int ssl_private_key_supports_signature_algorithm(SSL_HANDSHAKE *hs,
                                                 uint16_t sigalg);

/* ssl_public_key_verify verifies that the |signature| is valid for the public
 * key |pkey| and input |in|, using the signature algorithm |sigalg|. */
int ssl_public_key_verify(SSL *ssl, const uint8_t *signature,
                          size_t signature_len, uint16_t sigalg, EVP_PKEY *pkey,
                          const uint8_t *in, size_t in_len);


/* Custom extensions */

}  // namespace bssl

/* |SSL_CUSTOM_EXTENSION| is a structure that contains information about
 * custom-extension callbacks. It is defined unnamespaced for compatibility with
 * |STACK_OF(SSL_CUSTOM_EXTENSION)|. */
typedef struct ssl_custom_extension {
  SSL_custom_ext_add_cb add_callback;
  void *add_arg;
  SSL_custom_ext_free_cb free_callback;
  SSL_custom_ext_parse_cb parse_callback;
  void *parse_arg;
  uint16_t value;
} SSL_CUSTOM_EXTENSION;

DEFINE_STACK_OF(SSL_CUSTOM_EXTENSION)

namespace bssl {

void SSL_CUSTOM_EXTENSION_free(SSL_CUSTOM_EXTENSION *custom_extension);

int custom_ext_add_clienthello(SSL_HANDSHAKE *hs, CBB *extensions);
int custom_ext_parse_serverhello(SSL_HANDSHAKE *hs, int *out_alert,
                                 uint16_t value, const CBS *extension);
int custom_ext_parse_clienthello(SSL_HANDSHAKE *hs, int *out_alert,
                                 uint16_t value, const CBS *extension);
int custom_ext_add_serverhello(SSL_HANDSHAKE *hs, CBB *extensions);


/* Key shares. */

/* SSLKeyShare abstracts over Diffie-Hellman-like key exchanges. */
class SSLKeyShare {
 public:
  virtual ~SSLKeyShare() {}
  static constexpr bool kAllowUniquePtr = true;
  HAS_VIRTUAL_DESTRUCTOR

  /* Create returns a SSLKeyShare instance for use with group |group_id| or
   * nullptr on error. */
  static UniquePtr<SSLKeyShare> Create(uint16_t group_id);

  /* GroupID returns the group ID. */
  virtual uint16_t GroupID() const PURE_VIRTUAL;

  /* Offer generates a keypair and writes the public value to
   * |out_public_key|. It returns true on success and false on error. */
  virtual bool Offer(CBB *out_public_key) PURE_VIRTUAL;

  /* Accept performs a key exchange against the |peer_key| generated by |offer|.
   * On success, it returns true, writes the public value to |out_public_key|,
   * and sets |*out_secret| and |*out_secret_len| to a newly-allocated buffer
   * containing the shared secret. The caller must release this buffer with
   * |OPENSSL_free|. On failure, it returns false and sets |*out_alert| to an
   * alert to send to the peer.
   *
   * The default implementation calls |Offer| and then |Finish|, assuming a key
   * exchange protocol where the peers are symmetric.
   *
   * TODO(davidben): out_secret should be a smart pointer. */
  virtual bool Accept(CBB *out_public_key, uint8_t **out_secret,
                      size_t *out_secret_len, uint8_t *out_alert,
                      const uint8_t *peer_key, size_t peer_key_len);

  /* Finish performs a key exchange against the |peer_key| generated by
   * |Accept|. On success, it returns true and sets |*out_secret| and
   * |*out_secret_len| to a newly-allocated buffer containing the shared
   * secret. The caller must release this buffer with |OPENSSL_free|. On
   * failure, it returns zero and sets |*out_alert| to an alert to send to the
   * peer.
   *
   * TODO(davidben): out_secret should be a smart pointer. */
  virtual bool Finish(uint8_t **out_secret, size_t *out_secret_len,
                      uint8_t *out_alert, const uint8_t *peer_key,
                      size_t peer_key_len) PURE_VIRTUAL;
};

/* ssl_nid_to_group_id looks up the group corresponding to |nid|. On success, it
 * sets |*out_group_id| to the group ID and returns one. Otherwise, it returns
 * zero. */
int ssl_nid_to_group_id(uint16_t *out_group_id, int nid);

/* ssl_name_to_group_id looks up the group corresponding to the |name| string
 * of length |len|. On success, it sets |*out_group_id| to the group ID and
 * returns one. Otherwise, it returns zero. */
int ssl_name_to_group_id(uint16_t *out_group_id, const char *name, size_t len);


/* Handshake messages. */

struct SSLMessage {
  bool is_v2_hello;
  uint8_t type;
  CBS body;
  /* raw is the entire serialized handshake message, including the TLS or DTLS
   * message header. */
  CBS raw;
};

/* SSL_MAX_HANDSHAKE_FLIGHT is the number of messages, including
 * ChangeCipherSpec, in the longest handshake flight. Currently this is the
 * client's second leg in a full handshake when client certificates, NPN, and
 * Channel ID, are all enabled. */
#define SSL_MAX_HANDSHAKE_FLIGHT 7

/* ssl_max_handshake_message_len returns the maximum number of bytes permitted
 * in a handshake message for |ssl|. */
size_t ssl_max_handshake_message_len(const SSL *ssl);

/* ssl_read_message reads a message for the old |BIO|-based state machine. On
 * success, it returns one and sets |*out| to the current message. Otherwise, it
 * returns <= 0. */
int ssl_read_message(SSL *ssl, SSLMessage *out);

/* dtls_clear_incoming_messages releases all buffered incoming messages. */
void dtls_clear_incoming_messages(SSL *ssl);

/* dtls_has_incoming_messages returns one if there are buffered incoming
 * messages ahead of the current message and zero otherwise. */
int dtls_has_incoming_messages(const SSL *ssl);

struct DTLS_OUTGOING_MESSAGE {
  uint8_t *data;
  uint32_t len;
  uint16_t epoch;
  char is_ccs;
};

/* dtls_clear_outgoing_messages releases all buffered outgoing messages. */
void dtls_clear_outgoing_messages(SSL *ssl);


/* Callbacks. */

/* ssl_do_info_callback calls |ssl|'s info callback, if set. */
void ssl_do_info_callback(const SSL *ssl, int type, int value);

/* ssl_do_msg_callback calls |ssl|'s message callback, if set. */
void ssl_do_msg_callback(SSL *ssl, int is_write, int content_type,
                         const void *buf, size_t len);


/* Transport buffers. */

/* ssl_read_buffer returns a pointer to contents of the read buffer. */
uint8_t *ssl_read_buffer(SSL *ssl);

/* ssl_read_buffer_len returns the length of the read buffer. */
size_t ssl_read_buffer_len(const SSL *ssl);

/* ssl_read_buffer_extend_to extends the read buffer to the desired length. For
 * TLS, it reads to the end of the buffer until the buffer is |len| bytes
 * long. For DTLS, it reads a new packet and ignores |len|. It returns one on
 * success, zero on EOF, and a negative number on error.
 *
 * It is an error to call |ssl_read_buffer_extend_to| in DTLS when the buffer is
 * non-empty. */
int ssl_read_buffer_extend_to(SSL *ssl, size_t len);

/* ssl_read_buffer_consume consumes |len| bytes from the read buffer. It
 * advances the data pointer and decrements the length. The memory consumed will
 * remain valid until the next call to |ssl_read_buffer_extend| or it is
 * discarded with |ssl_read_buffer_discard|. */
void ssl_read_buffer_consume(SSL *ssl, size_t len);

/* ssl_read_buffer_discard discards the consumed bytes from the read buffer. If
 * the buffer is now empty, it releases memory used by it. */
void ssl_read_buffer_discard(SSL *ssl);

/* ssl_read_buffer_clear releases all memory associated with the read buffer and
 * zero-initializes it. */
void ssl_read_buffer_clear(SSL *ssl);

/* ssl_write_buffer_is_pending returns one if the write buffer has pending data
 * and zero if is empty. */
int ssl_write_buffer_is_pending(const SSL *ssl);

/* ssl_write_buffer_init initializes the write buffer. On success, it sets
 * |*out_ptr| to the start of the write buffer with space for up to |max_len|
 * bytes. It returns one on success and zero on failure. Call
 * |ssl_write_buffer_set_len| to complete initialization. */
int ssl_write_buffer_init(SSL *ssl, uint8_t **out_ptr, size_t max_len);

/* ssl_write_buffer_set_len is called after |ssl_write_buffer_init| to complete
 * initialization after |len| bytes are written to the buffer. */
void ssl_write_buffer_set_len(SSL *ssl, size_t len);

/* ssl_write_buffer_flush flushes the write buffer to the transport. It returns
 * one on success and <= 0 on error. For DTLS, whether or not the write
 * succeeds, the write buffer will be cleared. */
int ssl_write_buffer_flush(SSL *ssl);

/* ssl_write_buffer_clear releases all memory associated with the write buffer
 * and zero-initializes it. */
void ssl_write_buffer_clear(SSL *ssl);


/* Certificate functions. */

/* ssl_has_certificate returns one if a certificate and private key are
 * configured and zero otherwise. */
int ssl_has_certificate(const SSL *ssl);

/* ssl_parse_cert_chain parses a certificate list from |cbs| in the format used
 * by a TLS Certificate message. On success, it advances |cbs| and returns
 * true. Otherwise, it returns false and sets |*out_alert| to an alert to send
 * to the peer.
 *
 * If the list is non-empty then |*out_chain| and |*out_pubkey| will be set to
 * the certificate chain and the leaf certificate's public key
 * respectively. Otherwise, both will be set to nullptr.
 *
 * If the list is non-empty and |out_leaf_sha256| is non-NULL, it writes the
 * SHA-256 hash of the leaf to |out_leaf_sha256|. */
bool ssl_parse_cert_chain(uint8_t *out_alert,
                          UniquePtr<STACK_OF(CRYPTO_BUFFER)> *out_chain,
                          UniquePtr<EVP_PKEY> *out_pubkey,
                          uint8_t *out_leaf_sha256, CBS *cbs,
                          CRYPTO_BUFFER_POOL *pool);

/* ssl_add_cert_chain adds |ssl|'s certificate chain to |cbb| in the format used
 * by a TLS Certificate message. If there is no certificate chain, it emits an
 * empty certificate list. It returns one on success and zero on error. */
int ssl_add_cert_chain(SSL *ssl, CBB *cbb);

/* ssl_cert_check_digital_signature_key_usage parses the DER-encoded, X.509
 * certificate in |in| and returns one if doesn't specify a key usage or, if it
 * does, if it includes digitalSignature. Otherwise it pushes to the error
 * queue and returns zero. */
int ssl_cert_check_digital_signature_key_usage(const CBS *in);

/* ssl_cert_parse_pubkey extracts the public key from the DER-encoded, X.509
 * certificate in |in|. It returns an allocated |EVP_PKEY| or else returns
 * nullptr and pushes to the error queue. */
UniquePtr<EVP_PKEY> ssl_cert_parse_pubkey(const CBS *in);

/* ssl_parse_client_CA_list parses a CA list from |cbs| in the format used by a
 * TLS CertificateRequest message. On success, it returns a newly-allocated
 * |CRYPTO_BUFFER| list and advances |cbs|. Otherwise, it returns nullptr and
 * sets |*out_alert| to an alert to send to the peer. */
UniquePtr<STACK_OF(CRYPTO_BUFFER)> ssl_parse_client_CA_list(SSL *ssl,
                                                            uint8_t *out_alert,
                                                            CBS *cbs);

/* ssl_add_client_CA_list adds the configured CA list to |cbb| in the format
 * used by a TLS CertificateRequest message. It returns one on success and zero
 * on error. */
int ssl_add_client_CA_list(SSL *ssl, CBB *cbb);

/* ssl_check_leaf_certificate returns one if |pkey| and |leaf| are suitable as
 * a server's leaf certificate for |hs|. Otherwise, it returns zero and pushes
 * an error on the error queue. */
int ssl_check_leaf_certificate(SSL_HANDSHAKE *hs, EVP_PKEY *pkey,
                               const CRYPTO_BUFFER *leaf);

/* ssl_on_certificate_selected is called once the certificate has been selected.
 * It finalizes the certificate and initializes |hs->local_pubkey|. It returns
 * one on success and zero on error. */
int ssl_on_certificate_selected(SSL_HANDSHAKE *hs);


/* TLS 1.3 key derivation. */

/* tls13_init_key_schedule initializes the handshake hash and key derivation
 * state. The cipher suite and PRF hash must have been selected at this point.
 * It returns one on success and zero on error. */
int tls13_init_key_schedule(SSL_HANDSHAKE *hs);

/* tls13_init_early_key_schedule initializes the handshake hash and key
 * derivation state from the resumption secret to derive the early secrets. It
 * returns one on success and zero on error. */
int tls13_init_early_key_schedule(SSL_HANDSHAKE *hs);

/* tls13_advance_key_schedule incorporates |in| into the key schedule with
 * HKDF-Extract. It returns one on success and zero on error. */
int tls13_advance_key_schedule(SSL_HANDSHAKE *hs, const uint8_t *in,
                               size_t len);

/* tls13_set_traffic_key sets the read or write traffic keys to
 * |traffic_secret|. It returns one on success and zero on error. */
int tls13_set_traffic_key(SSL *ssl, enum evp_aead_direction_t direction,
                          const uint8_t *traffic_secret,
                          size_t traffic_secret_len);

/* tls13_derive_early_secrets derives the early traffic secret. It returns one
 * on success and zero on error. */
int tls13_derive_early_secrets(SSL_HANDSHAKE *hs);

/* tls13_derive_handshake_secrets derives the handshake traffic secret. It
 * returns one on success and zero on error. */
int tls13_derive_handshake_secrets(SSL_HANDSHAKE *hs);

/* tls13_rotate_traffic_key derives the next read or write traffic secret. It
 * returns one on success and zero on error. */
int tls13_rotate_traffic_key(SSL *ssl, enum evp_aead_direction_t direction);

/* tls13_derive_application_secrets derives the initial application data traffic
 * and exporter secrets based on the handshake transcripts and |master_secret|.
 * It returns one on success and zero on error. */
int tls13_derive_application_secrets(SSL_HANDSHAKE *hs);

/* tls13_derive_resumption_secret derives the |resumption_secret|. */
int tls13_derive_resumption_secret(SSL_HANDSHAKE *hs);

/* tls13_export_keying_material provides an exporter interface to use the
 * |exporter_secret|. */
int tls13_export_keying_material(SSL *ssl, uint8_t *out, size_t out_len,
                                 const char *label, size_t label_len,
                                 const uint8_t *context, size_t context_len,
                                 int use_context);

/* tls13_finished_mac calculates the MAC of the handshake transcript to verify
 * the integrity of the Finished message, and stores the result in |out| and
 * length in |out_len|. |is_server| is 1 if this is for the Server Finished and
 * 0 for the Client Finished. */
int tls13_finished_mac(SSL_HANDSHAKE *hs, uint8_t *out,
                       size_t *out_len, int is_server);

/* tls13_write_psk_binder calculates the PSK binder value and replaces the last
 * bytes of |msg| with the resulting value. It returns 1 on success, and 0 on
 * failure. */
int tls13_write_psk_binder(SSL_HANDSHAKE *hs, uint8_t *msg, size_t len);

/* tls13_verify_psk_binder verifies that the handshake transcript, truncated
 * up to the binders has a valid signature using the value of |session|'s
 * resumption secret. It returns 1 on success, and 0 on failure. */
int tls13_verify_psk_binder(SSL_HANDSHAKE *hs, SSL_SESSION *session,
                            const SSLMessage &msg, CBS *binders);


/* Handshake functions. */

enum ssl_hs_wait_t {
  ssl_hs_error,
  ssl_hs_ok,
  ssl_hs_read_message,
  ssl_hs_flush,
  ssl_hs_x509_lookup,
  ssl_hs_channel_id_lookup,
  ssl_hs_private_key_operation,
  ssl_hs_pending_ticket,
  ssl_hs_early_data_rejected,
  ssl_hs_read_end_of_early_data,
  ssl_hs_read_change_cipher_spec,
  ssl_hs_certificate_verify,
};

struct SSL_HANDSHAKE {
  explicit SSL_HANDSHAKE(SSL *ssl);
  ~SSL_HANDSHAKE();
  static constexpr bool kAllowUniquePtr = true;

  /* ssl is a non-owning pointer to the parent |SSL| object. */
  SSL *ssl;

  /* do_tls13_handshake runs the TLS 1.3 handshake. On completion, it returns
   * |ssl_hs_ok|. Otherwise, it returns a value corresponding to what operation
   * is needed to progress. */
  enum ssl_hs_wait_t (*do_tls13_handshake)(SSL_HANDSHAKE *hs);

  /* wait contains the operation |do_tls13_handshake| is currently blocking on
   * or |ssl_hs_ok| if none. */
  enum ssl_hs_wait_t wait = ssl_hs_ok;

  /* state contains one of the SSL3_ST_* values. */
  int state = SSL_ST_INIT;

  /* next_state is used when SSL_ST_FLUSH_DATA is entered */
  int next_state = 0;

  /* tls13_state is the internal state for the TLS 1.3 handshake. Its values
   * depend on |do_tls13_handshake| but the starting state is always zero. */
  int tls13_state = 0;

  /* min_version is the minimum accepted protocol version, taking account both
   * |SSL_OP_NO_*| and |SSL_CTX_set_min_proto_version| APIs. */
  uint16_t min_version = 0;

  /* max_version is the maximum accepted protocol version, taking account both
   * |SSL_OP_NO_*| and |SSL_CTX_set_max_proto_version| APIs. */
  uint16_t max_version = 0;

  /* session_id is the session ID in the ClientHello, used for the experimental
   * TLS 1.3 variant. */
  uint8_t session_id[SSL_MAX_SSL_SESSION_ID_LENGTH] = {0};
  uint8_t session_id_len = 0;

  size_t hash_len = 0;
  uint8_t secret[EVP_MAX_MD_SIZE] = {0};
  uint8_t early_traffic_secret[EVP_MAX_MD_SIZE] = {0};
  uint8_t client_handshake_secret[EVP_MAX_MD_SIZE] = {0};
  uint8_t server_handshake_secret[EVP_MAX_MD_SIZE] = {0};
  uint8_t client_traffic_secret_0[EVP_MAX_MD_SIZE] = {0};
  uint8_t server_traffic_secret_0[EVP_MAX_MD_SIZE] = {0};
  uint8_t expected_client_finished[EVP_MAX_MD_SIZE] = {0};

  union {
    /* sent is a bitset where the bits correspond to elements of kExtensions
     * in t1_lib.c. Each bit is set if that extension was sent in a
     * ClientHello. It's not used by servers. */
    uint32_t sent = 0;
    /* received is a bitset, like |sent|, but is used by servers to record
     * which extensions were received from a client. */
    uint32_t received;
  } extensions;

  union {
    /* sent is a bitset where the bits correspond to elements of
     * |client_custom_extensions| in the |SSL_CTX|. Each bit is set if that
     * extension was sent in a ClientHello. It's not used by servers. */
    uint16_t sent = 0;
    /* received is a bitset, like |sent|, but is used by servers to record
     * which custom extensions were received from a client. The bits here
     * correspond to |server_custom_extensions|. */
    uint16_t received;
  } custom_extensions;

  /* retry_group is the group ID selected by the server in HelloRetryRequest in
   * TLS 1.3. */
  uint16_t retry_group = 0;

  /* key_share is the current key exchange instance. */
  UniquePtr<SSLKeyShare> key_share;

  /* transcript is the current handshake transcript. */
  SSLTranscript transcript;

  /* cookie is the value of the cookie received from the server, if any. */
  uint8_t *cookie = nullptr;
  size_t cookie_len = 0;

  /* key_share_bytes is the value of the previously sent KeyShare extension by
   * the client in TLS 1.3. */
  uint8_t *key_share_bytes = nullptr;
  size_t key_share_bytes_len = 0;

  /* ecdh_public_key, for servers, is the key share to be sent to the client in
   * TLS 1.3. */
  uint8_t *ecdh_public_key = nullptr;
  size_t ecdh_public_key_len = 0;

  /* peer_sigalgs are the signature algorithms that the peer supports. These are
   * taken from the contents of the signature algorithms extension for a server
   * or from the CertificateRequest for a client. */
  uint16_t *peer_sigalgs = nullptr;
  /* num_peer_sigalgs is the number of entries in |peer_sigalgs|. */
  size_t num_peer_sigalgs = 0;

  /* peer_supported_group_list contains the supported group IDs advertised by
   * the peer. This is only set on the server's end. The server does not
   * advertise this extension to the client. */
  uint16_t *peer_supported_group_list = nullptr;
  size_t peer_supported_group_list_len = 0;

  /* peer_key is the peer's ECDH key for a TLS 1.2 client. */
  uint8_t *peer_key = nullptr;
  size_t peer_key_len = 0;

  /* server_params, in a TLS 1.2 server, stores the ServerKeyExchange
   * parameters. It has client and server randoms prepended for signing
   * convenience. */
  uint8_t *server_params = nullptr;
  size_t server_params_len = 0;

  /* peer_psk_identity_hint, on the client, is the psk_identity_hint sent by the
   * server when using a TLS 1.2 PSK key exchange. */
  UniquePtr<char> peer_psk_identity_hint;

  /* ca_names, on the client, contains the list of CAs received in a
   * CertificateRequest message. */
  UniquePtr<STACK_OF(CRYPTO_BUFFER)> ca_names;

  /* cached_x509_ca_names contains a cache of parsed versions of the elements
   * of |ca_names|. */
  STACK_OF(X509_NAME) *cached_x509_ca_names = nullptr;

  /* certificate_types, on the client, contains the set of certificate types
   * received in a CertificateRequest message. */
  uint8_t *certificate_types = nullptr;
  size_t num_certificate_types = 0;

  /* hostname, on the server, is the value of the SNI extension. */
  UniquePtr<char> hostname;

  /* local_pubkey is the public key we are authenticating as. */
  UniquePtr<EVP_PKEY> local_pubkey;

  /* peer_pubkey is the public key parsed from the peer's leaf certificate. */
  UniquePtr<EVP_PKEY> peer_pubkey;

  /* new_session is the new mutable session being established by the current
   * handshake. It should not be cached. */
  UniquePtr<SSL_SESSION> new_session;

  /* early_session is the session corresponding to the current 0-RTT state on
   * the client if |in_early_data| is true. */
  UniquePtr<SSL_SESSION> early_session;

  /* new_cipher is the cipher being negotiated in this handshake. */
  const SSL_CIPHER *new_cipher = nullptr;

  /* key_block is the record-layer key block for TLS 1.2 and earlier. */
  uint8_t *key_block = nullptr;
  uint8_t key_block_len = 0;

  /* scts_requested is one if the SCT extension is in the ClientHello. */
  unsigned scts_requested:1;

  /* needs_psk_binder if the ClientHello has a placeholder PSK binder to be
   * filled in. */
  unsigned needs_psk_binder:1;

  unsigned received_hello_retry_request:1;

  unsigned received_custom_extension:1;

  /* accept_psk_mode stores whether the client's PSK mode is compatible with our
   * preferences. */
  unsigned accept_psk_mode:1;

  /* cert_request is one if a client certificate was requested and zero
   * otherwise. */
  unsigned cert_request:1;

  /* certificate_status_expected is one if OCSP stapling was negotiated and the
   * server is expected to send a CertificateStatus message. (This is used on
   * both the client and server sides.) */
  unsigned certificate_status_expected:1;

  /* ocsp_stapling_requested is one if a client requested OCSP stapling. */
  unsigned ocsp_stapling_requested:1;

  /* should_ack_sni is used by a server and indicates that the SNI extension
   * should be echoed in the ServerHello. */
  unsigned should_ack_sni:1;

  /* in_false_start is one if there is a pending client handshake in False
   * Start. The client may write data at this point. */
  unsigned in_false_start:1;

  /* in_early_data is one if there is a pending handshake that has progressed
   * enough to send and receive early data. */
  unsigned in_early_data:1;

  /* early_data_offered is one if the client sent the early_data extension. */
  unsigned early_data_offered:1;

  /* can_early_read is one if application data may be read at this point in the
   * handshake. */
  unsigned can_early_read:1;

  /* can_early_write is one if application data may be written at this point in
   * the handshake. */
  unsigned can_early_write:1;

  /* next_proto_neg_seen is one of NPN was negotiated. */
  unsigned next_proto_neg_seen:1;

  /* ticket_expected is one if a TLS 1.2 NewSessionTicket message is to be sent
   * or received. */
  unsigned ticket_expected:1;

  /* extended_master_secret is one if the extended master secret extension is
   * negotiated in this handshake. */
  unsigned extended_master_secret:1;

  /* pending_private_key_op is one if there is a pending private key operation
   * in progress. */
  unsigned pending_private_key_op:1;

  /* client_version is the value sent or received in the ClientHello version. */
  uint16_t client_version = 0;

  /* early_data_read is the amount of early data that has been read by the
   * record layer. */
  uint16_t early_data_read = 0;

  /* early_data_written is the amount of early data that has been written by the
   * record layer. */
  uint16_t early_data_written = 0;
};

SSL_HANDSHAKE *ssl_handshake_new(SSL *ssl);

/* ssl_handshake_free releases all memory associated with |hs|. */
void ssl_handshake_free(SSL_HANDSHAKE *hs);

/* ssl_check_message_type checks if |msg| has type |type|. If so it returns
 * one. Otherwise, it sends an alert and returns zero. */
int ssl_check_message_type(SSL *ssl, const SSLMessage &msg, int type);

/* tls13_handshake runs the TLS 1.3 handshake. It returns one on success and <=
 * 0 on error. It sets |out_early_return| to one if we've completed the
 * handshake early. */
int tls13_handshake(SSL_HANDSHAKE *hs, int *out_early_return);

/* The following are implementations of |do_tls13_handshake| for the client and
 * server. */
enum ssl_hs_wait_t tls13_client_handshake(SSL_HANDSHAKE *hs);
enum ssl_hs_wait_t tls13_server_handshake(SSL_HANDSHAKE *hs);

/* The following functions return human-readable representations of the TLS 1.3
 * handshake states for debugging. */
const char *tls13_client_handshake_state(SSL_HANDSHAKE *hs);
const char *tls13_server_handshake_state(SSL_HANDSHAKE *hs);

/* tls13_post_handshake processes a post-handshake message. It returns one on
 * success and zero on failure. */
int tls13_post_handshake(SSL *ssl, const SSLMessage &msg);

int tls13_process_certificate(SSL_HANDSHAKE *hs, const SSLMessage &msg,
                              int allow_anonymous);
int tls13_process_certificate_verify(SSL_HANDSHAKE *hs, const SSLMessage &msg);

/* tls13_process_finished processes |msg| as a Finished message from the
 * peer. If |use_saved_value| is one, the verify_data is compared against
 * |hs->expected_client_finished| rather than computed fresh. */
int tls13_process_finished(SSL_HANDSHAKE *hs, const SSLMessage &msg,
                           int use_saved_value);

int tls13_add_certificate(SSL_HANDSHAKE *hs);

/* tls13_add_certificate_verify adds a TLS 1.3 CertificateVerify message to the
 * handshake. If it returns |ssl_private_key_retry|, it should be called again
 * to retry when the signing operation is completed. */
enum ssl_private_key_result_t tls13_add_certificate_verify(SSL_HANDSHAKE *hs);

int tls13_add_finished(SSL_HANDSHAKE *hs);
int tls13_process_new_session_ticket(SSL *ssl, const SSLMessage &msg);

int ssl_ext_key_share_parse_serverhello(SSL_HANDSHAKE *hs, uint8_t **out_secret,
                                        size_t *out_secret_len,
                                        uint8_t *out_alert, CBS *contents);
int ssl_ext_key_share_parse_clienthello(SSL_HANDSHAKE *hs, int *out_found,
                                        uint8_t **out_secret,
                                        size_t *out_secret_len,
                                        uint8_t *out_alert, CBS *contents);
int ssl_ext_key_share_add_serverhello(SSL_HANDSHAKE *hs, CBB *out);

int ssl_ext_pre_shared_key_parse_serverhello(SSL_HANDSHAKE *hs,
                                             uint8_t *out_alert, CBS *contents);
int ssl_ext_pre_shared_key_parse_clienthello(
    SSL_HANDSHAKE *hs, CBS *out_ticket, CBS *out_binders,
    uint32_t *out_obfuscated_ticket_age, uint8_t *out_alert, CBS *contents);
int ssl_ext_pre_shared_key_add_serverhello(SSL_HANDSHAKE *hs, CBB *out);

/* ssl_is_sct_list_valid does a shallow parse of the SCT list in |contents| and
 * returns one iff it's valid. */
int ssl_is_sct_list_valid(const CBS *contents);

int ssl_write_client_hello(SSL_HANDSHAKE *hs);

/* ssl_clear_tls13_state releases client state only needed for TLS 1.3. It
 * should be called once the version is known to be TLS 1.2 or earlier. */
void ssl_clear_tls13_state(SSL_HANDSHAKE *hs);

enum ssl_cert_verify_context_t {
  ssl_cert_verify_server,
  ssl_cert_verify_client,
  ssl_cert_verify_channel_id,
};

/* tls13_get_cert_verify_signature_input generates the message to be signed for
 * TLS 1.3's CertificateVerify message. |cert_verify_context| determines the
 * type of signature. It sets |*out| and |*out_len| to a newly allocated buffer
 * containing the result. The caller must free it with |OPENSSL_free| to release
 * it. This function returns one on success and zero on failure. */
int tls13_get_cert_verify_signature_input(
    SSL_HANDSHAKE *hs, uint8_t **out, size_t *out_len,
    enum ssl_cert_verify_context_t cert_verify_context);

/* ssl_negotiate_alpn negotiates the ALPN extension, if applicable. It returns
 * one on successful negotiation or if nothing was negotiated. It returns zero
 * and sets |*out_alert| to an alert on error. */
int ssl_negotiate_alpn(SSL_HANDSHAKE *hs, uint8_t *out_alert,
                       const SSL_CLIENT_HELLO *client_hello);

struct SSL_EXTENSION_TYPE {
  uint16_t type;
  int *out_present;
  CBS *out_data;
};

/* ssl_parse_extensions parses a TLS extensions block out of |cbs| and advances
 * it. It writes the parsed extensions to pointers denoted by |ext_types|. On
 * success, it fills in the |out_present| and |out_data| fields and returns one.
 * Otherwise, it sets |*out_alert| to an alert to send and returns zero. Unknown
 * extensions are rejected unless |ignore_unknown| is 1. */
int ssl_parse_extensions(const CBS *cbs, uint8_t *out_alert,
                         const SSL_EXTENSION_TYPE *ext_types,
                         size_t num_ext_types, int ignore_unknown);

/* ssl_verify_peer_cert verifies the peer certificate for |hs|. */
enum ssl_verify_result_t ssl_verify_peer_cert(SSL_HANDSHAKE *hs);


/* SSLKEYLOGFILE functions. */

/* ssl_log_secret logs |secret| with label |label|, if logging is enabled for
 * |ssl|. It returns one on success and zero on failure. */
int ssl_log_secret(const SSL *ssl, const char *label, const uint8_t *secret,
                   size_t secret_len);


/* ClientHello functions. */

int ssl_client_hello_init(SSL *ssl, SSL_CLIENT_HELLO *out,
                          const SSLMessage &msg);

int ssl_client_hello_get_extension(const SSL_CLIENT_HELLO *client_hello,
                                   CBS *out, uint16_t extension_type);

int ssl_client_cipher_list_contains_cipher(const SSL_CLIENT_HELLO *client_hello,
                                           uint16_t id);


/* GREASE. */

enum ssl_grease_index_t {
  ssl_grease_cipher = 0,
  ssl_grease_group,
  ssl_grease_extension1,
  ssl_grease_extension2,
  ssl_grease_version,
  ssl_grease_ticket_extension,
};

/* ssl_get_grease_value returns a GREASE value for |ssl|. For a given
 * connection, the values for each index will be deterministic. This allows the
 * same ClientHello be sent twice for a HelloRetryRequest or the same group be
 * advertised in both supported_groups and key_shares. */
uint16_t ssl_get_grease_value(const SSL *ssl, enum ssl_grease_index_t index);


/* Signature algorithms. */

/* tls1_parse_peer_sigalgs parses |sigalgs| as the list of peer signature
 * algorithms and saves them on |hs|. It returns one on success and zero on
 * error. */
int tls1_parse_peer_sigalgs(SSL_HANDSHAKE *hs, const CBS *sigalgs);

/* tls1_get_legacy_signature_algorithm sets |*out| to the signature algorithm
 * that should be used with |pkey| in TLS 1.1 and earlier. It returns one on
 * success and zero if |pkey| may not be used at those versions. */
int tls1_get_legacy_signature_algorithm(uint16_t *out, const EVP_PKEY *pkey);

/* tls1_choose_signature_algorithm sets |*out| to a signature algorithm for use
 * with |hs|'s private key based on the peer's preferences and the algorithms
 * supported. It returns one on success and zero on error. */
int tls1_choose_signature_algorithm(SSL_HANDSHAKE *hs, uint16_t *out);

/* tls12_add_verify_sigalgs adds the signature algorithms acceptable for the
 * peer signature to |out|. It returns one on success and zero on error. */
int tls12_add_verify_sigalgs(const SSL *ssl, CBB *out);

/* tls12_check_peer_sigalg checks if |sigalg| is acceptable for the peer
 * signature. It returns one on success and zero on error, setting |*out_alert|
 * to an alert to send. */
int tls12_check_peer_sigalg(SSL *ssl, uint8_t *out_alert, uint16_t sigalg);


/* Underdocumented functions.
 *
 * Functions below here haven't been touched up and may be underdocumented. */

#define TLSEXT_CHANNEL_ID_SIZE 128

/* From RFC4492, used in encoding the curve type in ECParameters */
#define NAMED_CURVE_TYPE 3

struct SSLCertConfig {
  EVP_PKEY *privatekey;

  /* chain contains the certificate chain, with the leaf at the beginning. The
   * first element of |chain| may be NULL to indicate that the leaf certificate
   * has not yet been set.
   *   If |chain| != NULL -> len(chain) >= 1
   *   If |chain[0]| == NULL -> len(chain) >= 2.
   *   |chain[1..]| != NULL */
  STACK_OF(CRYPTO_BUFFER) *chain;

  /* x509_chain may contain a parsed copy of |chain[1..]|. This is only used as
   * a cache in order to implement “get0” functions that return a non-owning
   * pointer to the certificate chain. */
  STACK_OF(X509) *x509_chain;

  /* x509_leaf may contain a parsed copy of the first element of |chain|. This
   * is only used as a cache in order to implement “get0” functions that return
   * a non-owning pointer to the certificate chain. */
  X509 *x509_leaf;

  /* x509_stash contains the last |X509| object append to the chain. This is a
   * workaround for some third-party code that continue to use an |X509| object
   * even after passing ownership with an “add0” function. */
  X509 *x509_stash;

  /* key_method, if non-NULL, is a set of callbacks to call for private key
   * operations. */
  const SSL_PRIVATE_KEY_METHOD *key_method;

  /* x509_method contains pointers to functions that might deal with |X509|
   * compatibility, or might be a no-op, depending on the application. */
  const SSL_X509_METHOD *x509_method;

  /* sigalgs, if non-NULL, is the set of signature algorithms supported by
   * |privatekey| in decreasing order of preference. */
  uint16_t *sigalgs;
  size_t num_sigalgs;

  /* Certificate setup callback: if set is called whenever a
   * certificate may be required (client or server). the callback
   * can then examine any appropriate parameters and setup any
   * certificates required. This allows advanced applications
   * to select certificates on the fly: for example based on
   * supported signature algorithms or curves. */
  int (*cert_cb)(SSL *ssl, void *arg);
  void *cert_cb_arg;

  /* Optional X509_STORE for certificate validation. If NULL the parent SSL_CTX
   * store is used instead. */
  X509_STORE *verify_store;

  /* Signed certificate timestamp list to be sent to the client, if requested */
  CRYPTO_BUFFER *signed_cert_timestamp_list;

  /* OCSP response to be sent to the client, if requested. */
  CRYPTO_BUFFER *ocsp_response;

  /* sid_ctx partitions the session space within a shared session cache or
   * ticket key. Only sessions with a matching value will be accepted. */
  uint8_t sid_ctx_length;
  uint8_t sid_ctx[SSL_MAX_SID_CTX_LENGTH];

  /* If enable_early_data is non-zero, early data can be sent and accepted. */
  unsigned enable_early_data:1;
};

/* ssl_crypto_x509_method provides the |SSL_X509_METHOD| functions using
 * crypto/x509. */
extern const SSL_X509_METHOD ssl_crypto_x509_method;

/* ssl_noop_x509_method provides the |SSL_X509_METHOD| functions that avoid
 * crypto/x509. */
extern const SSL_X509_METHOD ssl_noop_x509_method;

struct SSL3_RECORD {
  /* type is the record type. */
  uint8_t type;
  /* length is the number of unconsumed bytes in the record. */
  uint16_t length;
  /* data is a non-owning pointer to the first unconsumed byte of the record. */
  uint8_t *data;
};

struct SSL3_BUFFER {
  /* buf is the memory allocated for this buffer. */
  uint8_t *buf;
  /* offset is the offset into |buf| which the buffer contents start at. */
  uint16_t offset;
  /* len is the length of the buffer contents from |buf| + |offset|. */
  uint16_t len;
  /* cap is how much memory beyond |buf| + |offset| is available. */
  uint16_t cap;
};

/* An ssl_shutdown_t describes the shutdown state of one end of the connection,
 * whether it is alive or has been shutdown via close_notify or fatal alert. */
enum ssl_shutdown_t {
  ssl_shutdown_none = 0,
  ssl_shutdown_close_notify = 1,
  ssl_shutdown_fatal_alert = 2,
};

struct SSL3_STATE {
  uint8_t read_sequence[8];
  uint8_t write_sequence[8];

  uint8_t server_random[SSL3_RANDOM_SIZE];
  uint8_t client_random[SSL3_RANDOM_SIZE];

  /* read_buffer holds data from the transport to be processed. */
  SSL3_BUFFER read_buffer;
  /* write_buffer holds data to be written to the transport. */
  SSL3_BUFFER write_buffer;

  SSL3_RECORD rrec; /* each decoded record goes in here */

  /* partial write - check the numbers match */
  unsigned int wnum; /* number of bytes sent so far */
  int wpend_tot;     /* number bytes written */
  int wpend_type;
  int wpend_ret; /* number of bytes submitted */
  const uint8_t *wpend_buf;

  /* recv_shutdown is the shutdown state for the receive half of the
   * connection. */
  enum ssl_shutdown_t recv_shutdown;

  /* recv_shutdown is the shutdown state for the send half of the connection. */
  enum ssl_shutdown_t send_shutdown;

  int alert_dispatch;

  int total_renegotiations;

  /* early_data_skipped is the amount of early data that has been skipped by the
   * record layer. */
  uint16_t early_data_skipped;

  /* empty_record_count is the number of consecutive empty records received. */
  uint8_t empty_record_count;

  /* warning_alert_count is the number of consecutive warning alerts
   * received. */
  uint8_t warning_alert_count;

  /* key_update_count is the number of consecutive KeyUpdates received. */
  uint8_t key_update_count;

  /* skip_early_data instructs the record layer to skip unexpected early data
   * messages when 0RTT is rejected. */
  unsigned skip_early_data:1;

  /* have_version is true if the connection's final version is known. Otherwise
   * the version has not been negotiated yet. */
  unsigned have_version:1;

  /* v2_hello_done is true if the peer's V2ClientHello, if any, has been handled
   * and future messages should use the record layer. */
  unsigned v2_hello_done:1;

  /* is_v2_hello is true if the current handshake message was derived from a
   * V2ClientHello rather than received from the peer directly. */
  unsigned is_v2_hello:1;

  /* has_message is true if the current handshake message has been returned
   * at least once by |get_message| and false otherwise. */
  unsigned has_message:1;

  /* initial_handshake_complete is true if the initial handshake has
   * completed. */
  unsigned initial_handshake_complete:1;

  /* session_reused indicates whether a session was resumed. */
  unsigned session_reused:1;

  unsigned send_connection_binding:1;

  /* In a client, this means that the server supported Channel ID and that a
   * Channel ID was sent. In a server it means that we echoed support for
   * Channel IDs and that tlsext_channel_id will be valid after the
   * handshake. */
  unsigned tlsext_channel_id_valid:1;

  /* key_update_pending is one if we have a KeyUpdate acknowledgment
   * outstanding. */
  unsigned key_update_pending:1;

  /* wpend_pending is one if we have a pending write outstanding. */
  unsigned wpend_pending:1;

  uint8_t send_alert[2];

  /* pending_flight is the pending outgoing flight. This is used to flush each
   * handshake flight in a single write. |write_buffer| must be written out
   * before this data. */
  BUF_MEM *pending_flight;

  /* pending_flight_offset is the number of bytes of |pending_flight| which have
   * been successfully written. */
  uint32_t pending_flight_offset;

  /* aead_read_ctx is the current read cipher state. */
  SSLAEADContext *aead_read_ctx;

  /* aead_write_ctx is the current write cipher state. */
  SSLAEADContext *aead_write_ctx;

  /* hs is the handshake state for the current handshake or NULL if there isn't
   * one. */
  SSL_HANDSHAKE *hs;

  uint8_t write_traffic_secret[EVP_MAX_MD_SIZE];
  uint8_t read_traffic_secret[EVP_MAX_MD_SIZE];
  uint8_t exporter_secret[EVP_MAX_MD_SIZE];
  uint8_t early_exporter_secret[EVP_MAX_MD_SIZE];
  uint8_t write_traffic_secret_len;
  uint8_t read_traffic_secret_len;
  uint8_t exporter_secret_len;
  uint8_t early_exporter_secret_len;

  /* Connection binding to prevent renegotiation attacks */
  uint8_t previous_client_finished[12];
  uint8_t previous_client_finished_len;
  uint8_t previous_server_finished_len;
  uint8_t previous_server_finished[12];

  /* State pertaining to the pending handshake.
   *
   * TODO(davidben): Move everything not needed after the handshake completes to
   * |hs| and remove this. */
  struct {
    uint8_t new_mac_secret_len;
    uint8_t new_key_len;
    uint8_t new_fixed_iv_len;
  } tmp;

  /* established_session is the session established by the connection. This
   * session is only filled upon the completion of the handshake and is
   * immutable. */
  SSL_SESSION *established_session;

  /* Next protocol negotiation. For the client, this is the protocol that we
   * sent in NextProtocol and is set when handling ServerHello extensions.
   *
   * For a server, this is the client's selected_protocol from NextProtocol and
   * is set when handling the NextProtocol message, before the Finished
   * message. */
  uint8_t *next_proto_negotiated;
  size_t next_proto_negotiated_len;

  /* ALPN information
   * (we are in the process of transitioning from NPN to ALPN.) */

  /* In a server these point to the selected ALPN protocol after the
   * ClientHello has been processed. In a client these contain the protocol
   * that the server selected once the ServerHello has been processed. */
  uint8_t *alpn_selected;
  size_t alpn_selected_len;

  /* For a server:
   *     If |tlsext_channel_id_valid| is true, then this contains the
   *     verified Channel ID from the client: a P256 point, (x,y), where
   *     each are big-endian values. */
  uint8_t tlsext_channel_id[64];

  /* ticket_age_skew is the difference, in seconds, between the client-sent
   * ticket age and the server-computed value in TLS 1.3 server connections
   * which resumed a session. */
  int32_t ticket_age_skew;
};

/* lengths of messages */
#define DTLS1_COOKIE_LENGTH 256

#define DTLS1_RT_HEADER_LENGTH 13

#define DTLS1_HM_HEADER_LENGTH 12

#define DTLS1_CCS_HEADER_LENGTH 1

#define DTLS1_AL_HEADER_LENGTH 2

struct hm_header_st {
  uint8_t type;
  uint32_t msg_len;
  uint16_t seq;
  uint32_t frag_off;
  uint32_t frag_len;
};

/* An hm_fragment is an incoming DTLS message, possibly not yet assembled. */
struct hm_fragment {
  /* type is the type of the message. */
  uint8_t type;
  /* seq is the sequence number of this message. */
  uint16_t seq;
  /* msg_len is the length of the message body. */
  uint32_t msg_len;
  /* data is a pointer to the message, including message header. It has length
   * |DTLS1_HM_HEADER_LENGTH| + |msg_len|. */
  uint8_t *data;
  /* reassembly is a bitmask of |msg_len| bits corresponding to which parts of
   * the message have been received. It is NULL if the message is complete. */
  uint8_t *reassembly;
};

struct OPENSSL_timeval {
  uint64_t tv_sec;
  uint32_t tv_usec;
};

struct DTLS1_STATE {
  /* send_cookie is true if we are resending the ClientHello with a cookie from
   * a HelloVerifyRequest. */
  bool send_cookie:1;

  /* has_change_cipher_spec is true if we have received a ChangeCipherSpec from
   * the peer in this epoch. */
  bool has_change_cipher_spec:1;

  /* outgoing_messages_complete is true if |outgoing_messages| has been
   * completed by an attempt to flush it. Future calls to |add_message| and
   * |add_change_cipher_spec| will start a new flight. */
  bool outgoing_messages_complete:1;

  /* flight_has_reply is true if the current outgoing flight is complete and has
   * processed at least one message. This is used to detect whether we or the
   * peer sent the final flight. */
  bool flight_has_reply:1;

  uint8_t cookie[DTLS1_COOKIE_LENGTH];
  size_t cookie_len;

  /* The current data and handshake epoch.  This is initially undefined, and
   * starts at zero once the initial handshake is completed. */
  uint16_t r_epoch;
  uint16_t w_epoch;

  /* records being received in the current epoch */
  DTLS1_BITMAP bitmap;

  uint16_t handshake_write_seq;
  uint16_t handshake_read_seq;

  /* save last sequence number for retransmissions */
  uint8_t last_write_sequence[8];
  SSLAEADContext *last_aead_write_ctx;

  /* incoming_messages is a ring buffer of incoming handshake messages that have
   * yet to be processed. The front of the ring buffer is message number
   * |handshake_read_seq|, at position |handshake_read_seq| %
   * |SSL_MAX_HANDSHAKE_FLIGHT|. */
  hm_fragment *incoming_messages[SSL_MAX_HANDSHAKE_FLIGHT];

  /* outgoing_messages is the queue of outgoing messages from the last handshake
   * flight. */
  DTLS_OUTGOING_MESSAGE outgoing_messages[SSL_MAX_HANDSHAKE_FLIGHT];
  uint8_t outgoing_messages_len;

  /* outgoing_written is the number of outgoing messages that have been
   * written. */
  uint8_t outgoing_written;
  /* outgoing_offset is the number of bytes of the next outgoing message have
   * been written. */
  uint32_t outgoing_offset;

  unsigned int mtu; /* max DTLS packet size */

  /* num_timeouts is the number of times the retransmit timer has fired since
   * the last time it was reset. */
  unsigned int num_timeouts;

  /* Indicates when the last handshake msg or heartbeat sent will
   * timeout. */
  struct OPENSSL_timeval next_timeout;

  /* timeout_duration_ms is the timeout duration in milliseconds. */
  unsigned timeout_duration_ms;
};

/* SSLConnection backs the public |SSL| type. Due to compatibility constraints,
 * it is a base class for |ssl_st|. */
struct SSLConnection {
  /* method is the method table corresponding to the current protocol (DTLS or
   * TLS). */
  const SSL_PROTOCOL_METHOD *method;

  /* version is the protocol version. */
  uint16_t version;

  /* conf_max_version is the maximum acceptable protocol version configured by
   * |SSL_set_max_proto_version|. Note this version is normalized in DTLS and is
   * further constrainted by |SSL_OP_NO_*|. */
  uint16_t conf_max_version;

  /* conf_min_version is the minimum acceptable protocol version configured by
   * |SSL_set_min_proto_version|. Note this version is normalized in DTLS and is
   * further constrainted by |SSL_OP_NO_*|. */
  uint16_t conf_min_version;

  /* tls13_variant is the variant of TLS 1.3 we are using for this
   * configuration. */
  enum tls13_variant_t tls13_variant;

  uint16_t max_send_fragment;

  /* There are 2 BIO's even though they are normally both the same. This is so
   * data can be read and written to different handlers */

  BIO *rbio; /* used by SSL_read */
  BIO *wbio; /* used by SSL_write */

  int (*handshake_func)(SSL_HANDSHAKE *hs);

  BUF_MEM *init_buf; /* buffer used during init */

  SSL3_STATE *s3;  /* SSLv3 variables */
  DTLS1_STATE *d1; /* DTLSv1 variables */

  /* callback that allows applications to peek at protocol messages */
  void (*msg_callback)(int write_p, int version, int content_type,
                       const void *buf, size_t len, SSL *ssl, void *arg);
  void *msg_callback_arg;

  X509_VERIFY_PARAM *param;

  /* crypto */
  struct ssl_cipher_preference_list_st *cipher_list;

  /* session info */

  /* client cert? */
  /* This is used to hold the server certificate used */
  CERT *cert;

  /* This holds a variable that indicates what we were doing when a 0 or -1 is
   * returned.  This is needed for non-blocking IO so we know what request
   * needs re-doing when in SSL_accept or SSL_connect */
  int rwstate;

  /* initial_timeout_duration_ms is the default DTLS timeout duration in
   * milliseconds. It's used to initialize the timer any time it's restarted. */
  unsigned initial_timeout_duration_ms;

  /* session is the configured session to be offered by the client. This session
   * is immutable. */
  SSL_SESSION *session;

  int (*verify_callback)(int ok,
                         X509_STORE_CTX *ctx); /* fail if callback returns 0 */

  enum ssl_verify_result_t (*custom_verify_callback)(SSL *ssl,
                                                     uint8_t *out_alert);

  void (*info_callback)(const SSL *ssl, int type, int value);

  /* Server-only: psk_identity_hint is the identity hint to send in
   * PSK-based key exchanges. */
  char *psk_identity_hint;

  unsigned int (*psk_client_callback)(SSL *ssl, const char *hint,
                                      char *identity,
                                      unsigned int max_identity_len,
                                      uint8_t *psk, unsigned int max_psk_len);
  unsigned int (*psk_server_callback)(SSL *ssl, const char *identity,
                                      uint8_t *psk, unsigned int max_psk_len);

  SSL_CTX *ctx;

  /* extra application data */
  CRYPTO_EX_DATA ex_data;

  /* for server side, keep the list of CA_dn we can use */
  STACK_OF(CRYPTO_BUFFER) *client_CA;

  /* cached_x509_client_CA is a cache of parsed versions of the elements of
   * |client_CA|. */
  STACK_OF(X509_NAME) *cached_x509_client_CA;

  uint32_t options; /* protocol behaviour */
  uint32_t mode;    /* API behaviour */
  uint32_t max_cert_list;
  char *tlsext_hostname;
  size_t supported_group_list_len;
  uint16_t *supported_group_list; /* our list */

  /* session_ctx is the |SSL_CTX| used for the session cache and related
   * settings. */
  SSL_CTX *session_ctx;

  /* srtp_profiles is the list of configured SRTP protection profiles for
   * DTLS-SRTP. */
  STACK_OF(SRTP_PROTECTION_PROFILE) *srtp_profiles;

  /* srtp_profile is the selected SRTP protection profile for
   * DTLS-SRTP. */
  const SRTP_PROTECTION_PROFILE *srtp_profile;

  /* The client's Channel ID private key. */
  EVP_PKEY *tlsext_channel_id_private;

  /* For a client, this contains the list of supported protocols in wire
   * format. */
  uint8_t *alpn_client_proto_list;
  unsigned alpn_client_proto_list_len;

  /* renegotiate_mode controls how peer renegotiation attempts are handled. */
  enum ssl_renegotiate_mode_t renegotiate_mode;

  /* verify_mode is a bitmask of |SSL_VERIFY_*| values. */
  uint8_t verify_mode;

  /* server is true iff the this SSL* is the server half. Note: before the SSL*
   * is initialized by either SSL_set_accept_state or SSL_set_connect_state,
   * the side is not determined. In this state, server is always false. */
  unsigned server:1;

  /* quiet_shutdown is true if the connection should not send a close_notify on
   * shutdown. */
  unsigned quiet_shutdown:1;

  /* Enable signed certificate time stamps. Currently client only. */
  unsigned signed_cert_timestamps_enabled:1;

  /* ocsp_stapling_enabled is only used by client connections and indicates
   * whether OCSP stapling will be requested. */
  unsigned ocsp_stapling_enabled:1;

  /* tlsext_channel_id_enabled is copied from the |SSL_CTX|. For a server,
   * means that we'll accept Channel IDs from clients. For a client, means that
   * we'll advertise support. */
  unsigned tlsext_channel_id_enabled:1;

  /* retain_only_sha256_of_client_certs is true if we should compute the SHA256
   * hash of the peer's certificate and then discard it to save memory and
   * session space. Only effective on the server side. */
  unsigned retain_only_sha256_of_client_certs:1;

  /* early_data_accepted is true if early data was accepted by the server. */
  unsigned early_data_accepted:1;
};

/* From draft-ietf-tls-tls13-18, used in determining PSK modes. */
#define SSL_PSK_KE     0x0
#define SSL_PSK_DHE_KE 0x1

/* From draft-ietf-tls-tls13-16, used in determining whether to respond with a
 * KeyUpdate. */
#define SSL_KEY_UPDATE_NOT_REQUESTED 0
#define SSL_KEY_UPDATE_REQUESTED 1

/* kMaxEarlyDataAccepted is the advertised number of plaintext bytes of early
 * data that will be accepted. This value should be slightly below
 * kMaxEarlyDataSkipped in tls_record.c, which is measured in ciphertext. */
static const size_t kMaxEarlyDataAccepted = 14336;

CERT *ssl_cert_new(const SSL_X509_METHOD *x509_method);
CERT *ssl_cert_dup(CERT *cert);
void ssl_cert_clear_certs(CERT *cert);
void ssl_cert_free(CERT *cert);
int ssl_set_cert(CERT *cert, UniquePtr<CRYPTO_BUFFER> buffer);
int ssl_is_key_type_supported(int key_type);
/* ssl_compare_public_and_private_key returns one if |pubkey| is the public
 * counterpart to |privkey|. Otherwise it returns zero and pushes a helpful
 * message on the error queue. */
int ssl_compare_public_and_private_key(const EVP_PKEY *pubkey,
                                       const EVP_PKEY *privkey);
int ssl_cert_check_private_key(const CERT *cert, const EVP_PKEY *privkey);
int ssl_get_new_session(SSL_HANDSHAKE *hs, int is_server);
int ssl_encrypt_ticket(SSL *ssl, CBB *out, const SSL_SESSION *session);
int ssl_ctx_rotate_ticket_encryption_key(SSL_CTX *ctx);

/* ssl_session_new returns a newly-allocated blank |SSL_SESSION| or nullptr on
 * error. */
UniquePtr<SSL_SESSION> ssl_session_new(const SSL_X509_METHOD *x509_method);

/* SSL_SESSION_parse parses an |SSL_SESSION| from |cbs| and advances |cbs| over
 * the parsed data. */
UniquePtr<SSL_SESSION> SSL_SESSION_parse(CBS *cbs,
                                         const SSL_X509_METHOD *x509_method,
                                         CRYPTO_BUFFER_POOL *pool);

/* ssl_session_is_context_valid returns one if |session|'s session ID context
 * matches the one set on |ssl| and zero otherwise. */
int ssl_session_is_context_valid(const SSL *ssl, const SSL_SESSION *session);

/* ssl_session_is_time_valid returns one if |session| is still valid and zero if
 * it has expired. */
int ssl_session_is_time_valid(const SSL *ssl, const SSL_SESSION *session);

/* ssl_session_is_resumable returns one if |session| is resumable for |hs| and
 * zero otherwise. */
int ssl_session_is_resumable(const SSL_HANDSHAKE *hs,
                             const SSL_SESSION *session);

/* SSL_SESSION_protocol_version returns the protocol version associated with
 * |session|. */
uint16_t SSL_SESSION_protocol_version(const SSL_SESSION *session);

/* SSL_SESSION_get_digest returns the digest used in |session|. */
const EVP_MD *SSL_SESSION_get_digest(const SSL_SESSION *session);

void ssl_set_session(SSL *ssl, SSL_SESSION *session);

enum ssl_session_result_t {
  ssl_session_success,
  ssl_session_error,
  ssl_session_retry,
  ssl_session_ticket_retry,
};

/* ssl_get_prev_session looks up the previous session based on |client_hello|.
 * On success, it sets |*out_session| to the session or nullptr if none was
 * found. If the session could not be looked up synchronously, it returns
 * |ssl_session_retry| and should be called again. If a ticket could not be
 * decrypted immediately it returns |ssl_session_ticket_retry| and should also
 * be called again. Otherwise, it returns |ssl_session_error|.  */
enum ssl_session_result_t ssl_get_prev_session(
    SSL *ssl, UniquePtr<SSL_SESSION> *out_session, int *out_tickets_supported,
    int *out_renew_ticket, const SSL_CLIENT_HELLO *client_hello);

/* The following flags determine which parts of the session are duplicated. */
#define SSL_SESSION_DUP_AUTH_ONLY 0x0
#define SSL_SESSION_INCLUDE_TICKET 0x1
#define SSL_SESSION_INCLUDE_NONAUTH 0x2
#define SSL_SESSION_DUP_ALL \
  (SSL_SESSION_INCLUDE_TICKET | SSL_SESSION_INCLUDE_NONAUTH)

/* SSL_SESSION_dup returns a newly-allocated |SSL_SESSION| with a copy of the
 * fields in |session| or nullptr on error. The new session is non-resumable and
 * must be explicitly marked resumable once it has been filled in. */
OPENSSL_EXPORT UniquePtr<SSL_SESSION> SSL_SESSION_dup(SSL_SESSION *session,
                                                      int dup_flags);

/* ssl_session_rebase_time updates |session|'s start time to the current time,
 * adjusting the timeout so the expiration time is unchanged. */
void ssl_session_rebase_time(SSL *ssl, SSL_SESSION *session);

/* ssl_session_renew_timeout calls |ssl_session_rebase_time| and renews
 * |session|'s timeout to |timeout| (measured from the current time). The
 * renewal is clamped to the session's auth_timeout. */
void ssl_session_renew_timeout(SSL *ssl, SSL_SESSION *session,
                               uint32_t timeout);

void ssl_cipher_preference_list_free(
    struct ssl_cipher_preference_list_st *cipher_list);

/* ssl_get_cipher_preferences returns the cipher preference list for TLS 1.2 and
 * below. */
const struct ssl_cipher_preference_list_st *ssl_get_cipher_preferences(
    const SSL *ssl);

void ssl_update_cache(SSL_HANDSHAKE *hs, int mode);

int ssl3_get_finished(SSL_HANDSHAKE *hs);
int ssl3_send_alert(SSL *ssl, int level, int desc);
bool ssl3_get_message(SSL *ssl, SSLMessage *out);
int ssl3_read_message(SSL *ssl);
void ssl3_next_message(SSL *ssl);

int ssl3_send_finished(SSL_HANDSHAKE *hs);
int ssl3_dispatch_alert(SSL *ssl);
int ssl3_read_app_data(SSL *ssl, int *out_got_handshake, uint8_t *buf, int len,
                       int peek);
int ssl3_read_change_cipher_spec(SSL *ssl);
void ssl3_read_close_notify(SSL *ssl);
int ssl3_read_handshake_bytes(SSL *ssl, uint8_t *buf, int len);
int ssl3_write_app_data(SSL *ssl, int *out_needs_handshake, const uint8_t *buf,
                        int len);
int ssl3_output_cert_chain(SSL *ssl);

int ssl3_new(SSL *ssl);
void ssl3_free(SSL *ssl);
int ssl3_accept(SSL_HANDSHAKE *hs);
int ssl3_connect(SSL_HANDSHAKE *hs);

int ssl3_init_message(SSL *ssl, CBB *cbb, CBB *body, uint8_t type);
int ssl3_finish_message(SSL *ssl, CBB *cbb, uint8_t **out_msg, size_t *out_len);
int ssl3_add_message(SSL *ssl, uint8_t *msg, size_t len);
int ssl3_add_change_cipher_spec(SSL *ssl);
int ssl3_add_alert(SSL *ssl, uint8_t level, uint8_t desc);
int ssl3_flush_flight(SSL *ssl);

int dtls1_init_message(SSL *ssl, CBB *cbb, CBB *body, uint8_t type);
int dtls1_finish_message(SSL *ssl, CBB *cbb, uint8_t **out_msg,
                         size_t *out_len);
int dtls1_add_message(SSL *ssl, uint8_t *msg, size_t len);
int dtls1_add_change_cipher_spec(SSL *ssl);
int dtls1_add_alert(SSL *ssl, uint8_t level, uint8_t desc);
int dtls1_flush_flight(SSL *ssl);

/* ssl_add_message_cbb finishes the handshake message in |cbb| and adds it to
 * the pending flight. It returns one on success and zero on error. */
int ssl_add_message_cbb(SSL *ssl, CBB *cbb);

/* ssl_hash_message incorporates |msg| into the handshake hash. It returns one
 * on success and zero on allocation failure. */
bool ssl_hash_message(SSL_HANDSHAKE *hs, const SSLMessage &msg);

/* dtls1_get_record reads a new input record. On success, it places it in
 * |ssl->s3->rrec| and returns one. Otherwise it returns <= 0 on error or if
 * more data is needed. */
int dtls1_get_record(SSL *ssl);

int dtls1_read_app_data(SSL *ssl, int *out_got_handshake, uint8_t *buf, int len,
                        int peek);
int dtls1_read_change_cipher_spec(SSL *ssl);
void dtls1_read_close_notify(SSL *ssl);

int dtls1_write_app_data(SSL *ssl, int *out_needs_handshake, const uint8_t *buf,
                         int len);

/* dtls1_write_record sends a record. It returns one on success and <= 0 on
 * error. */
int dtls1_write_record(SSL *ssl, int type, const uint8_t *buf, size_t len,
                       enum dtls1_use_epoch_t use_epoch);

int dtls1_send_finished(SSL *ssl, int a, int b, const char *sender, int slen);
int dtls1_retransmit_outgoing_messages(SSL *ssl);
void dtls1_clear_record_buffer(SSL *ssl);
int dtls1_parse_fragment(CBS *cbs, struct hm_header_st *out_hdr,
                         CBS *out_body);
int dtls1_check_timeout_num(SSL *ssl);
int dtls1_handshake_write(SSL *ssl);

void dtls1_start_timer(SSL *ssl);
void dtls1_stop_timer(SSL *ssl);
int dtls1_is_timer_expired(SSL *ssl);
unsigned int dtls1_min_mtu(void);

int dtls1_new(SSL *ssl);
int dtls1_accept(SSL *ssl);
int dtls1_connect(SSL *ssl);
void dtls1_free(SSL *ssl);

bool dtls1_get_message(SSL *ssl, SSLMessage *out);
int dtls1_read_message(SSL *ssl);
void dtls1_next_message(SSL *ssl);
int dtls1_dispatch_alert(SSL *ssl);

int tls1_change_cipher_state(SSL_HANDSHAKE *hs, int which);
int tls1_generate_master_secret(SSL_HANDSHAKE *hs, uint8_t *out,
                                const uint8_t *premaster, size_t premaster_len);

/* tls1_get_grouplist sets |*out_group_ids| and |*out_group_ids_len| to the
 * locally-configured group preference list. */
void tls1_get_grouplist(SSL *ssl, const uint16_t **out_group_ids,
                        size_t *out_group_ids_len);

/* tls1_check_group_id returns one if |group_id| is consistent with
 * locally-configured group preferences. */
int tls1_check_group_id(SSL *ssl, uint16_t group_id);

/* tls1_get_shared_group sets |*out_group_id| to the first preferred shared
 * group between client and server preferences and returns one. If none may be
 * found, it returns zero. */
int tls1_get_shared_group(SSL_HANDSHAKE *hs, uint16_t *out_group_id);

/* tls1_set_curves converts the array of |ncurves| NIDs pointed to by |curves|
 * into a newly allocated array of TLS group IDs. On success, the function
 * returns one and writes the array to |*out_group_ids| and its size to
 * |*out_group_ids_len|. Otherwise, it returns zero. */
int tls1_set_curves(uint16_t **out_group_ids, size_t *out_group_ids_len,
                    const int *curves, size_t ncurves);

/* tls1_set_curves_list converts the string of curves pointed to by |curves|
 * into a newly allocated array of TLS group IDs. On success, the function
 * returns one and writes the array to |*out_group_ids| and its size to
 * |*out_group_ids_len|. Otherwise, it returns zero. */
int tls1_set_curves_list(uint16_t **out_group_ids, size_t *out_group_ids_len,
                         const char *curves);

/* ssl_add_clienthello_tlsext writes ClientHello extensions to |out|. It
 * returns one on success and zero on failure. The |header_len| argument is the
 * length of the ClientHello written so far and is used to compute the padding
 * length. (It does not include the record header.) */
int ssl_add_clienthello_tlsext(SSL_HANDSHAKE *hs, CBB *out, size_t header_len);

int ssl_add_serverhello_tlsext(SSL_HANDSHAKE *hs, CBB *out);
int ssl_parse_clienthello_tlsext(SSL_HANDSHAKE *hs,
                                 const SSL_CLIENT_HELLO *client_hello);
int ssl_parse_serverhello_tlsext(SSL_HANDSHAKE *hs, CBS *cbs);

#define tlsext_tick_md EVP_sha256

/* ssl_process_ticket processes a session ticket from the client. It returns
 * one of:
 *   |ssl_ticket_aead_success|: |*out_session| is set to the parsed session and
 *       |*out_renew_ticket| is set to whether the ticket should be renewed.
 *   |ssl_ticket_aead_ignore_ticket|: |*out_renew_ticket| is set to whether a
 *       fresh ticket should be sent, but the given ticket cannot be used.
 *   |ssl_ticket_aead_retry|: the ticket could not be immediately decrypted.
 *       Retry later.
 *   |ssl_ticket_aead_error|: an error occured that is fatal to the connection. */
enum ssl_ticket_aead_result_t ssl_process_ticket(
    SSL *ssl, UniquePtr<SSL_SESSION> *out_session, int *out_renew_ticket,
    const uint8_t *ticket, size_t ticket_len, const uint8_t *session_id,
    size_t session_id_len);

/* tls1_verify_channel_id processes |msg| as a Channel ID message, and verifies
 * the signature. If the key is valid, it saves the Channel ID and returns
 * one. Otherwise, it returns zero. */
int tls1_verify_channel_id(SSL_HANDSHAKE *hs, const SSLMessage &msg);

/* tls1_write_channel_id generates a Channel ID message and puts the output in
 * |cbb|. |ssl->tlsext_channel_id_private| must already be set before calling.
 * This function returns one on success and zero on error. */
int tls1_write_channel_id(SSL_HANDSHAKE *hs, CBB *cbb);

/* tls1_channel_id_hash computes the hash to be signed by Channel ID and writes
 * it to |out|, which must contain at least |EVP_MAX_MD_SIZE| bytes. It returns
 * one on success and zero on failure. */
int tls1_channel_id_hash(SSL_HANDSHAKE *hs, uint8_t *out, size_t *out_len);

int tls1_record_handshake_hashes_for_channel_id(SSL_HANDSHAKE *hs);

/* ssl_do_channel_id_callback checks runs |ssl->ctx->channel_id_cb| if
 * necessary. It returns one on success and zero on fatal error. Note that, on
 * success, |ssl->tlsext_channel_id_private| may be unset, in which case the
 * operation should be retried later. */
int ssl_do_channel_id_callback(SSL *ssl);

/* ssl3_can_false_start returns one if |ssl| is allowed to False Start and zero
 * otherwise. */
int ssl3_can_false_start(const SSL *ssl);

/* ssl_can_write returns one if |ssl| is allowed to write and zero otherwise. */
int ssl_can_write(const SSL *ssl);

/* ssl_can_read returns one if |ssl| is allowed to read and zero otherwise. */
int ssl_can_read(const SSL *ssl);

void ssl_get_current_time(const SSL *ssl, struct OPENSSL_timeval *out_clock);
void ssl_ctx_get_current_time(const SSL_CTX *ctx,
                              struct OPENSSL_timeval *out_clock);

/* ssl_reset_error_state resets state for |SSL_get_error|. */
void ssl_reset_error_state(SSL *ssl);


/* Utility macros */

#if defined(__clang__)
/* SSL_FALLTHROUGH annotates a fallthough case in a switch statement. */
#define SSL_FALLTHROUGH [[clang::fallthrough]]
#else
#define SSL_FALLTHROUGH
#endif

}  // namespace bssl


/* Opaque C types.
 *
 * The following types are exported to C code as public typedefs, so they must
 * be defined outside of the namespace. */

/* ssl_method_st backs the public |SSL_METHOD| type. It is a compatibility
 * structure to support the legacy version-locked methods. */
struct ssl_method_st {
  /* version, if non-zero, is the only protocol version acceptable to an
   * SSL_CTX initialized from this method. */
  uint16_t version;
  /* method is the underlying SSL_PROTOCOL_METHOD that initializes the
   * SSL_CTX. */
  const SSL_PROTOCOL_METHOD *method;
  /* x509_method contains pointers to functions that might deal with |X509|
   * compatibility, or might be a no-op, depending on the application. */
  const SSL_X509_METHOD *x509_method;
};

/* ssl_protocol_method_st, aka |SSL_PROTOCOL_METHOD| abstracts between TLS and
 * DTLS. */
struct ssl_protocol_method_st {
  /* is_dtls is one if the protocol is DTLS and zero otherwise. */
  char is_dtls;
  int (*ssl_new)(SSL *ssl);
  void (*ssl_free)(SSL *ssl);
  /* get_message sets |*out| to the current handshake message and returns true
   * if one has been received. It returns false if more input is needed. */
  bool (*get_message)(SSL *ssl, bssl::SSLMessage *out);
  /* read_message reads additional handshake data for |get_message|. On success,
   * it returns one. Otherwise, it returns <= 0. */
  int (*read_message)(SSL *ssl);
  /* next_message is called to release the current handshake message. */
  void (*next_message)(SSL *ssl);
  /* read_app_data reads up to |len| bytes of application data into |buf|. On
   * success, it returns the number of bytes read. Otherwise, it returns <= 0
   * and sets |*out_got_handshake| to whether the failure was due to a
   * post-handshake handshake message. If so, any handshake messages consumed
   * may be read with |get_message|. */
  int (*read_app_data)(SSL *ssl, int *out_got_handshake, uint8_t *buf, int len,
                       int peek);
  int (*read_change_cipher_spec)(SSL *ssl);
  void (*read_close_notify)(SSL *ssl);
  int (*write_app_data)(SSL *ssl, int *out_needs_handshake, const uint8_t *buf,
                        int len);
  int (*dispatch_alert)(SSL *ssl);
  /* supports_cipher returns one if |cipher| is supported by this protocol and
   * zero otherwise. */
  int (*supports_cipher)(const SSL_CIPHER *cipher);
  /* init_message begins a new handshake message of type |type|. |cbb| is the
   * root CBB to be passed into |finish_message|. |*body| is set to a child CBB
   * the caller should write to. It returns one on success and zero on error. */
  int (*init_message)(SSL *ssl, CBB *cbb, CBB *body, uint8_t type);
  /* finish_message finishes a handshake message. It sets |*out_msg| to a
   * newly-allocated buffer with the serialized message. The caller must
   * release it with |OPENSSL_free| when done. It returns one on success and
   * zero on error. */
  int (*finish_message)(SSL *ssl, CBB *cbb, uint8_t **out_msg, size_t *out_len);
  /* add_message adds a handshake message to the pending flight. It returns one
   * on success and zero on error. In either case, it takes ownership of |msg|
   * and releases it with |OPENSSL_free| when done. */
  int (*add_message)(SSL *ssl, uint8_t *msg, size_t len);
  /* add_change_cipher_spec adds a ChangeCipherSpec record to the pending
   * flight. It returns one on success and zero on error. */
  int (*add_change_cipher_spec)(SSL *ssl);
  /* add_alert adds an alert to the pending flight. It returns one on success
   * and zero on error. */
  int (*add_alert)(SSL *ssl, uint8_t level, uint8_t desc);
  /* flush_flight flushes the pending flight to the transport. It returns one on
   * success and <= 0 on error. */
  int (*flush_flight)(SSL *ssl);
  /* on_handshake_complete is called when the handshake is complete. */
  void (*on_handshake_complete)(SSL *ssl);
  /* set_read_state sets |ssl|'s read cipher state to |aead_ctx|. It returns
   * one on success and zero if changing the read state is forbidden at this
   * point. */
  int (*set_read_state)(SSL *ssl,
                        bssl::UniquePtr<bssl::SSLAEADContext> aead_ctx);
  /* set_write_state sets |ssl|'s write cipher state to |aead_ctx|. It returns
   * one on success and zero if changing the write state is forbidden at this
   * point. */
  int (*set_write_state)(SSL *ssl,
                         bssl::UniquePtr<bssl::SSLAEADContext> aead_ctx);
};

struct ssl_x509_method_st {
  /* check_client_CA_list returns one if |names| is a good list of X.509
   * distinguished names and zero otherwise. This is used to ensure that we can
   * reject unparsable values at handshake time when using crypto/x509. */
  int (*check_client_CA_list)(STACK_OF(CRYPTO_BUFFER) *names);

  /* cert_clear frees and NULLs all X509 certificate-related state. */
  void (*cert_clear)(CERT *cert);
  /* cert_free frees all X509-related state. */
  void (*cert_free)(CERT *cert);
  /* cert_flush_cached_chain drops any cached |X509|-based certificate chain
   * from |cert|. */
  /* cert_dup duplicates any needed fields from |cert| to |new_cert|. */
  void (*cert_dup)(CERT *new_cert, const CERT *cert);
  void (*cert_flush_cached_chain)(CERT *cert);
  /* cert_flush_cached_chain drops any cached |X509|-based leaf certificate
   * from |cert|. */
  void (*cert_flush_cached_leaf)(CERT *cert);

  /* session_cache_objects fills out |sess->x509_peer| and |sess->x509_chain|
   * from |sess->certs| and erases |sess->x509_chain_without_leaf|. It returns
   * one on success or zero on error. */
  int (*session_cache_objects)(SSL_SESSION *session);
  /* session_dup duplicates any needed fields from |session| to |new_session|.
   * It returns one on success or zero on error. */
  int (*session_dup)(SSL_SESSION *new_session, const SSL_SESSION *session);
  /* session_clear frees any X509-related state from |session|. */
  void (*session_clear)(SSL_SESSION *session);
  /* session_verify_cert_chain verifies the certificate chain in |session|,
   * sets |session->verify_result| and returns one on success or zero on
   * error. */
  int (*session_verify_cert_chain)(SSL_SESSION *session, SSL *ssl,
                                   uint8_t *out_alert);

  /* hs_flush_cached_ca_names drops any cached |X509_NAME|s from |hs|. */
  void (*hs_flush_cached_ca_names)(bssl::SSL_HANDSHAKE *hs);
  /* ssl_new does any neccessary initialisation of |ssl|. It returns one on
   * success or zero on error. */
  int (*ssl_new)(SSL *ssl);
  /* ssl_free frees anything created by |ssl_new|. */
  void (*ssl_free)(SSL *ssl);
  /* ssl_flush_cached_client_CA drops any cached |X509_NAME|s from |ssl|. */
  void (*ssl_flush_cached_client_CA)(SSL *ssl);
  /* ssl_auto_chain_if_needed runs the deprecated auto-chaining logic if
   * necessary. On success, it updates |ssl|'s certificate configuration as
   * needed and returns one. Otherwise, it returns zero. */
  int (*ssl_auto_chain_if_needed)(SSL *ssl);
  /* ssl_ctx_new does any neccessary initialisation of |ctx|. It returns one on
   * success or zero on error. */
  int (*ssl_ctx_new)(SSL_CTX *ctx);
  /* ssl_ctx_free frees anything created by |ssl_ctx_new|. */
  void (*ssl_ctx_free)(SSL_CTX *ctx);
  /* ssl_ctx_flush_cached_client_CA drops any cached |X509_NAME|s from |ctx|. */
  void (*ssl_ctx_flush_cached_client_CA)(SSL_CTX *ssl);
};

/* ssl_st backs the public |SSL| type. It subclasses the true type so that
 * SSLConnection may be a C++ type with methods and destructor without
 * polluting the global namespace. */
struct ssl_st : public bssl::SSLConnection {};

struct cert_st : public bssl::SSLCertConfig {};


#endif /* OPENSSL_HEADER_SSL_INTERNAL_H */
