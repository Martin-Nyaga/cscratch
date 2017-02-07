#ifndef _SC_HASHMAP_
#define _SC_HASHMAP_

// Key Value node
typedef struct NodeH {
	char* key;
	char* value;
	struct NodeH* next;
} NodeH;

// Linked list Bucket
typedef struct BucketH {
	NodeH* head;
	int count;
} BucketH;

// Hashmap
typedef struct ScHashmap {
	 // Total number of buckets in the Hashmap
	int max_size;
	// Contents
	BucketH* contents;
} ScHashmap;

void sc_hashmap_init(ScHashmap*, int);
void sc_hashmap_store(ScHashmap*, char*, char*, int);
NodeH* sc_hashmap_lookup(ScHashmap*, char*, int);
int sc_hash_key(ScHashmap*, char*);
NodeH* sc_bucket_find_key(BucketH*, char*);
void sc_bucket_insert(BucketH*, NodeH*);
void sc_print_hash(ScHashmap*, int);
void sc_print_formatted_kv_pair(int, int, char*, char*);

#define NORMAL_FORMAT 0
#define POINTER_VALUE_FORMAT 1

#define SHOW_LOOKUP_ERRORS 1
#define HIDE_LOOKUP_ERRORS 0

#define MAKE_STRING_COPIES 1
#define NO_STRING_COPIES 0
#endif
