#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

int main(){
	ScHashmap hashmap;

	sc_hashmap_init(&hashmap, 100);

	sc_hashmap_store(&hashmap, "Pointers", "Rock");
	sc_hashmap_store(&hashmap, "Hello", "World");
	sc_hashmap_store(&hashmap, "How", "Are");
	sc_hashmap_store(&hashmap, "You", "Today");
	sc_hashmap_store(&hashmap, "Foo", "Bar");
	sc_hashmap_store(&hashmap, "Might", "Right");
	sc_hashmap_store(&hashmap, "Fight", "Light");
	sc_hashmap_store(&hashmap, "And", "Then");
	sc_print_hash(&hashmap);

	NodeH* node_ptr = sc_hashmap_lookup(&hashmap, "Pointers");

	printf("%s\n", node_ptr->value);

	return 0;
}

void sc_hashmap_init(ScHashmap* hashmap, int num_buckets){
	// Allocate memory fro all buckets
	BucketH* new_contents_ptr = (BucketH*) malloc(num_buckets * sizeof(BucketH));

	hashmap->contents = new_contents_ptr;
	hashmap->max_size = num_buckets;

	int i;
	// Initialize buckets as empty stores
	for(i = 0; i < num_buckets; i++){
		BucketH bucket;
		bucket.head = NULL;
		bucket.count = 0;
		hashmap->contents[i] = bucket;
	}
}

void sc_hashmap_store(ScHashmap* hashmap, char* key, char* value){
	// Get the bucket
	int bucket_num = sc_hash_key(hashmap, key);
	BucketH* bucket_ptr = hashmap->contents + bucket_num;

	// Ensure that no such key exists in bucket
	NodeH* existing_node_ptr = sc_bucket_find_key(bucket_ptr, key);
	if(existing_node_ptr != NULL){
		fprintf(stderr, "Duplicate key found in bucket! Key: '%s' will not be stored.\n", key);
		return;
	}

	// Init the node
	NodeH* node_ptr = (NodeH*) malloc(sizeof(NodeH));
	node_ptr->key = key;
	node_ptr->value = value;

	sc_bucket_insert(bucket_ptr, node_ptr);
}

NodeH* sc_hashmap_lookup(ScHashmap* hashmap, char* key){
	// Get the bucket
	int bucket_num = sc_hash_key(hashmap, key);
	BucketH* bucket_ptr = hashmap->contents + bucket_num;

	// Find key in bucket
	NodeH* node_ptr = sc_bucket_find_key(bucket_ptr, key);

	// Print error if null
	if(node_ptr == NULL){
		fprintf(stderr, "Key not found in hashmap!\n");
	}

	// Return the pointer
	return node_ptr;
}

int sc_hash_key(ScHashmap* hashmap, char* str){
	int len = strlen(str);
	int i;
	int total = 0;

	for(i = 0; i < len; i++){
		int d = str[i];
		total += d;
	}

	total = total % hashmap->max_size;
	return total;
}

// Find key in bucket given by bucket_ptr
// by traversing the linked list
// Returns null if not found
NodeH* sc_bucket_find_key(BucketH* bucket_ptr, char* key){
	// If bucket is empty, return
	if(bucket_ptr->count == 0){
		return NULL;
	}

	// Start at head
	NodeH* node_ptr = bucket_ptr->head;
 do {
		// If you find key, return
		if(strcmp(key, node_ptr->key) == 0){
			return node_ptr;
		} else {
			// Go to next node
			node_ptr = node_ptr->next;
		}
	} while(node_ptr->next != NULL);

	// If not found, return null
	return NULL;
}

void sc_bucket_insert(BucketH* bucket_ptr, NodeH* node_ptr){
	// if Bucket is Empty
	if (bucket_ptr->count == 0) {
		// Insert node as head of bucket
		// And set it as last
		node_ptr->next = NULL;
		bucket_ptr->head = node_ptr;
	} else {
		// Insert Node at beginning of linked list
		// Store previous head
		NodeH* prev_head = bucket_ptr->head;
		
		// Assign new head of the bucket
		bucket_ptr->head = node_ptr;

		// Set next to previous head
		node_ptr->next = prev_head;
	}

	// Increase bucket count
	bucket_ptr->count++;
}

void sc_print_hash(ScHashmap* hashmap){
	int i;

	printf("[ \n");
	for(i = 0; i < hashmap->max_size; i++){
		BucketH bucket = hashmap->contents[i];

		if(bucket.count > 0){
			printf("  Bucket %d => {\n", i);
			
			// Traverse linked List
			NodeH* node_ptr = bucket.head;
			while(node_ptr != NULL){
				printf("    '%s' => '%s'\n", node_ptr->key, node_ptr->value);
				node_ptr = node_ptr->next;
			}

			printf("  },\n");
		}
	}

	printf("]\n");	
}