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
void sc_hashmap_store(ScHashmap*, char*, char*);
NodeH* sc_hashmap_lookup(ScHashmap*, char*);
int sc_hash_key(ScHashmap*, char*);
NodeH* sc_bucket_find_key(BucketH*, char*);
void sc_bucket_insert(BucketH*, NodeH*);
void sc_print_hash(ScHashmap*);

#endif
