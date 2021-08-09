

typedef struct {
  int a;
  long b;
  double c;
  float d;
  char* e;
} DemoObj;


typedef struct {
 long user_id;
 int user_type;
 char* gender;
 char* city;
} User;


typedef struct {
  long doc_id;
  int doc_type;
} Doc;


typedef struct {
  User user;
  Doc doc;
} Feature;
