#include "wsp_hash_oaat.h"

void wsp_hash_oaat_initialize(struct wsp_hash_oaat_s *s) {
  s->_state = 1111;
  s->state = 1111111111;
}

void wsp_hash_oaat_transform(unsigned long i, unsigned long input_count,
                             const uint8_t *input, struct wsp_hash_oaat_s *s) {
  while (i != input_count) {
    s->state += input[i];
    s->state += s->state << 3;
    s->state = (s->state << 19) | (s->state >> 13);
    s->_state += s->state + 1;
    i++;
  }
}

void wsp_hash_oaat_finalize(struct wsp_hash_oaat_s *s) {
  s->state ^= s->_state >> 1;
  s->state += (s->_state << 27) | (s->_state >> 5);
  s->_state ^= s->state >> 4;
  s->state += (s->_state << 8) | (s->_state >> 24);
  s->state ^= s->_state >> 3;
  s->_state += (s->state << 14) | (s->state >> 18);
  s->_state += (s->_state >> 7) ^ ((s->state << 9) | (s->state >> 23));
  s->state ^= s->_state;
}

uint32_t wsp_hash_oaat(unsigned long input_count, const uint8_t *input) {
  uint32_t _state = 1111;
  uint32_t state = 1111111111;
  unsigned long i = 0;

  while (i != input_count) {
    state += input[i];
    state += state << 3;
    state = (state << 19) | (state >> 13);
    _state += state + 1;
    i++;
  }

  state ^= _state >> 1;
  state += (_state << 27) | (_state >> 5);
  _state ^= state >> 4;
  state += (_state << 8) | (_state >> 24);
  state ^= _state >> 3;
  _state += (state << 14) | (state >> 18);
  _state += (_state >> 7) ^ ((state << 9) | (state >> 23));
  return _state ^ state;
}
