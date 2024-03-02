#include "struct_fn_ptr.h"



static uint __get_file_size(file_t* file) {
   assert(file);
   FILE* fp = fopen(file->name, &file->mode);

   fseek(fp,0 , SEEK_END);
   uint size = ftell(fp);

   rewind(fp);
   return size;
}

static bool __copy_to_other(file_t* self_source, file_t* other_dest){
      assert_2ptrs(self_source,  other_dest);

      if ( other_dest->mode != 'w'  ){
          warn_printf("destination file isnt set to w  mode");
          return false;
      }

      FILE* src = fopen(self_source->name, "r");
      FILE* dest = fopen(other_dest->name, "w");

      if (!src || !dest){
         warn_printf("failed in opening files");
         if (src) fclose(src);
         if (dest) fclose(dest);
         return false;
      }

      int ch;

      while ( (ch = fgetc(src) ) != EOF) {
          fputc(ch, dest);
      }

      fclose(src);
      fclose(dest);

      return true;
}

static bool __copy_to_self(file_t* other_source, file_t* self_destination){
      assert_2ptrs(other_source,  self_destination);

      if ( self_destination->mode != 'w'  ){
          warn_printf("self destination file isnt set to w mode");
          return false;
      }

      FILE* src = fopen(other_source->name, "r");
      FILE* dest = fopen(self_destination->name, "w");

      if (!src || !dest){
         warn_printf("failed in opening files");
         if (src) fclose(src);
         if (dest) fclose(dest);
         return false;
      }

      int ch;

      while ((ch = fgetc(src) ) != EOF) {
          fputc(ch, dest);
      }

      fclose(src);
      fclose(dest);

      return true;
}

static bool __append_to_other(file_t* self_source, file_t* other_dest){
      assert_2ptrs(self_source,  other_dest);

      if ( other_dest->mode != 'a'  ){
          warn_printf("destination file isnt set to a mode");
          return false;
      }

      FILE* src = fopen(self_source->name, "r");
      FILE* dest = fopen(other_dest->name, "a");

      if (!src || !dest){
         warn_printf("failed in opening files");
         if (src) fclose(src);
         if (dest) fclose(dest);
         return false;
      }

      int ch;

      while ( (ch = fgetc(src) ) != EOF) {
          fputc(ch, dest);
      }

      fclose(src);
      fclose(dest);

      return true;
}

static bool __append_to_self(file_t* other_source, file_t* self_destination){
      assert_2ptrs(other_source,  self_destination);

      if (self_destination->mode != 'a'){
          warn_printf("self destination file isnt set to a mode");
          return false;
      }

      FILE* src = fopen(other_source->name, "r");
      FILE* dest = fopen(self_destination->name, "a");

      if (!src || !dest){
         warn_printf("failed in opening files");
         if (src) fclose(src);
         if (dest) fclose(dest);
         return false;
      }

      int ch;
      while ((ch = fgetc(src) ) != EOF) {
          fputc(ch, dest);
      }

      fclose(src);
      fclose(dest);

      return true;
}

static bool __append_to_file(file_t* file, const char* text){
      assert_2ptrs(file, text);

      FILE* fp = fopen(file->name, &file->mode);

      null_errno_check(fp);

      fputs(text ,fp);
      fclose(fp);
}

file_t* create_file_struct(const char* name, const char mode){
   assert(name);

   file_t* file = (file_t*) malloc(sizeof(file_t));
   assert(file);

   strcpy(file->name,name);
   file->mode = mode;

   memset(&file->fn, 0, sizeof(file->fn));

   switch (mode) {

      case 'a' :
         file->fn.a.get_file_size = __get_file_size;
         file->fn.a.append_to_other = __append_to_other;
         file->fn.a.copy_to_other = __copy_to_other;
         file->fn.a.append_to_self = __append_to_self;

      break;

      case 'w' :
         file->fn.w.get_file_size = __get_file_size;
         file->fn.w.copy_to_other = __copy_to_other;
         file->fn.w.copy_to_self = __copy_to_self;
         file->fn.w.append_to_other = __append_to_other;

      break;

      case 'r' :
         file->fn.r.get_file_size = __get_file_size;
         file->fn.r.copy_to_other = __copy_to_other;
         file->fn.r.append_to_other = __append_to_other;
      break;

      default:
         printf("At create_file_struct() function, FILE opening mode is invalid.  File: %s , Line:%d", __FILE__, __LINE__);
         free(file);
         exit(1);
   }
  
   //file->get_file_size = __get_file_size;

   return file;
}


int main(){

  file_t* file2 = create_file_struct("test.txt",'r');

  file_t* file1 = create_file_struct("test.txt",'r');

  printf( "%d \n",file1->fn.r.get_file_size(file1) );
  
  file1->fn.r.
  //printf("%p \n",file1->fn.a.copy_to_other);

}