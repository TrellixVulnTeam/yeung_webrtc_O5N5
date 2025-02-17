/*
 * Copyright (C) 2011 Ericsson AB. All rights reserved.
 * Copyright (C) 2013 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer
 *    in the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Ericsson nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MediaStreamComponent_h
#define MediaStreamComponent_h

#include <memory>
#include "platform/audio/AudioSourceProvider.h"
#include "platform/heap/Handle.h"
#include "platform/wtf/Forward.h"
#include "platform/wtf/ThreadingPrimitives.h"
#include "platform/wtf/text/WTFString.h"
#include "public/platform/WebMediaStreamTrack.h"

namespace blink {

class MediaStreamSource;
class WebAudioSourceProvider;

// A MediaStreamComponent is a MediaStreamTrack.
// TODO(hta): Consider merging the two classes.

class PLATFORM_EXPORT MediaStreamComponent final
    : public GarbageCollectedFinalized<MediaStreamComponent> {
  USING_PRE_FINALIZER(MediaStreamComponent, Dispose);

 private:
  static int GenerateUniqueId();

 public:
  // This class represents whatever data the Web layer uses to represent
  // a track. It needs to be able to answer the getSettings question.
  class TrackData {
    USING_FAST_MALLOC(TrackData);

   public:
    virtual void GetSettings(WebMediaStreamTrack::Settings&) = 0;
    virtual ~TrackData() {}
  };

  static MediaStreamComponent* Create(MediaStreamSource*);
  static MediaStreamComponent* Create(const String& id, MediaStreamSource*);

  MediaStreamComponent* Clone() const;

  // |m_trackData| may hold pointers to GC objects indirectly, and it may touch
  // eagerly finalized objects in destruction.
  // So this class runs pre-finalizer to finalize |m_trackData| promptly.
  void Dispose();

  MediaStreamSource* Source() const { return source_.Get(); }

  // This is the same as the id of the |MediaStreamTrack|. It is unique in most
  // contexts but collisions can occur e.g. if tracks are created by different
  // |RTCPeerConnection|s or a remote track ID is signaled to be added, removed
  // and then re-added resulting in a new track object the second time around.
  String Id() const { return id_; }
  // Uniquely identifies this component.
  int UniqueId() const { return unique_id_; }
  bool Enabled() const { return enabled_; }
  void SetEnabled(bool enabled) { enabled_ = enabled; }
  bool Muted() const { return muted_; }
  void SetMuted(bool muted) { muted_ = muted; }
  WebMediaStreamTrack::ContentHintType ContentHint() { return content_hint_; }
  void SetContentHint(WebMediaStreamTrack::ContentHintType);
  AudioSourceProvider* GetAudioSourceProvider() { return &source_provider_; }
  void SetSourceProvider(WebAudioSourceProvider* provider) {
    source_provider_.Wrap(provider);
  }

  TrackData* GetTrackData() const { return track_data_.get(); }
  void SetTrackData(std::unique_ptr<TrackData> track_data) {
    track_data_ = std::move(track_data);
  }
  void GetSettings(WebMediaStreamTrack::Settings&);

  DECLARE_TRACE();

 private:
  MediaStreamComponent(const String& id, MediaStreamSource*);
  MediaStreamComponent(const String& id,
                       MediaStreamSource*,
                       bool enabled,
                       bool muted,
                       WebMediaStreamTrack::ContentHintType);

  // AudioSourceProviderImpl wraps a WebAudioSourceProvider::provideInput()
  // calls into chromium to get a rendered audio stream.

  class PLATFORM_EXPORT AudioSourceProviderImpl final
      : public AudioSourceProvider {
   public:
    AudioSourceProviderImpl() : web_audio_source_provider_(0) {}

    ~AudioSourceProviderImpl() override {}

    // Wraps the given blink::WebAudioSourceProvider to
    // blink::AudioSourceProvider.
    void Wrap(WebAudioSourceProvider*);

    // blink::AudioSourceProvider
    void ProvideInput(AudioBus*, size_t frames_to_process) override;

   private:
    WebAudioSourceProvider* web_audio_source_provider_;
    Mutex provide_input_lock_;
  };

  AudioSourceProviderImpl source_provider_;
  Member<MediaStreamSource> source_;
  String id_;
  int unique_id_;
  bool enabled_;
  bool muted_;
  WebMediaStreamTrack::ContentHintType content_hint_;
  std::unique_ptr<TrackData> track_data_;
};

typedef HeapVector<Member<MediaStreamComponent>> MediaStreamComponentVector;

}  // namespace blink

#endif  // MediaStreamComponent_h
