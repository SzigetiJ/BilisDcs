/*****************************************
 * This example file shows how to use
 * DcsHashSet as uniq filter.
 *****************************************/

#include "DcsHashSet.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define WORD_LEN 20
#define HASHSET_CAPACITY 40
#define BUCKETS 50

typedef char Word[WORD_LEN];
typedef char *WordPtr;


ElementIdx word_hash(ElementPtr a) {
  WordPtr aword = (WordPtr)a;
  ElementIdx retv = 0;
  int len = strlen(aword);
  for (int i = 0; i < len; ++i)
    retv += aword[i];
  return retv;
}

bool word_equals(ElementPtr a, ElementPtr b) {
  WordPtr aword = (WordPtr) a;
  WordPtr bword = (WordPtr) b;
  return strcmp(aword, bword) == 0;
}

void print_word_hashset_content(const DcsHashSet *hs) {
  for (DcsIterator i = dcshashset_begin(hs);
          !dcshashset_iterator_equals(hs, i, dcshashset_end(hs));
          i = dcshashset_next_iterator(hs, i)) {
    WordPtr item = (WordPtr) dcshashset_deref_iterator(hs, i);
    printf("#%u:\t%s\n", (unsigned int) i, item);
  }
}

int tokenize_sentence(WordPtr sentence, Word *words, unsigned int words_capacity) {
  int word_idx=0;
  WordPtr token_begin=sentence;
  WordPtr token_end;
  WordPtr sentence_end = sentence + strlen(sentence);
  bool go = true;
  while (go) {
    token_end = strchr(token_begin, ' ');
    if (token_end==NULL) {
      go = false;
      token_end = sentence_end;
    }
    memcpy(words[word_idx], token_begin, token_end - token_begin);
    words[word_idx][token_end-token_begin] = 0;
    ++word_idx;
    if (word_idx == words_capacity) {
      go = false;
    }
    token_begin = token_end + 1;
  }
  return word_idx;
}

WordPtr sentence="How much wood would a woodchuck chuck if a woodchuck could chuck wood";

int main(int argc, const char *argv[]) {
  // store
  Word input_raw[HASHSET_CAPACITY];
  Word hashset_dat_raw[HASHSET_CAPACITY];

  // hashset init
  ElementIdx auxidx_a[DCSHASHSET_AUXIDX_SIZE(BUCKETS, HASHSET_CAPACITY)];
  bool auxflag_a[DCSHASHSET_AUXFLAG_SIZE(BUCKETS, HASHSET_CAPACITY)];
  DcsHashSet word_hs = dcshashset_init(
          sizeof (Word), HASHSET_CAPACITY, BUCKETS,
          (ElementPtr) hashset_dat_raw, auxidx_a, auxflag_a,
          word_hash, word_equals);

  // preparation (sentence to words)
  int word_idx = tokenize_sentence(sentence, input_raw, HASHSET_CAPACITY);

  // populating hashset
  for (int i=0; i<word_idx; ++i) {
    printf("Inserting word #%d: \"%s\"...", i, input_raw[i]);
    bool insert_success = dcshashset_insert(&word_hs, (ElementPtr)input_raw[i]);
    printf("%s\n", (insert_success?"OK.":"FAILED."));
  }

  // results
  printf("NUMBER OF DISTINCT WORDS: %u\n", dcshashset_size(&word_hs));
  printf("SET OF DISTINCT WORDS:\n");
  print_word_hashset_content(&word_hs);

  return 0;
}
