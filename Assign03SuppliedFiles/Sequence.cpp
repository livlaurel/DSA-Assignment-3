// FILE: Sequence.cpp
// CLASS IMPLEMENTED: sequence (see sequence.h for documentation)
// INVARIANT for the sequence ADT:
//   1. The number of items in the sequence is in the member variable
//      used;
//   2. The actual items of the sequence are stored in a partially
//      filled array. The array is a dynamic array, pointed to by
//      the member variable data. For an empty sequence, we do not
//      care what is stored in any of data; for a non-empty sequence
//      the items in the sequence are stored in data[0] through
//      data[used-1], and we don't care what's in the rest of data.
//   3. The size of the dynamic array is in the member variable
//      capacity.
//   4. The index of the current item is in the member variable
//      current_index. If there is no valid current item, then
//      current_index will be set to the same number as used.
//      NOTE: Setting current_index to be the same as used to
//            indicate "no current item exists" is a good choice
//            for at least the following reasons:
//            (a) For a non-empty sequence, used is non-zero and
//                a current_index equal to used indexes an element
//                that is (just) outside the valid range. This
//                gives us a simple and useful way to indicate
//                whether the sequence has a current item or not:
//                a current_index in the valid range indicates
//                that there's a current item, and a current_index
//                outside the valid range indicates otherwise.
//            (b) The rule remains applicable for an empty sequence,
//                where used is zero: there can't be any current
//                item in an empty sequence, so we set current_index
//                to zero (= used), which is (sort of just) outside
//                the valid range (no index is valid in this case).
//            (c) It simplifies the logic for implementing the
//                advance function: when the precondition is met
//                (sequence has a current item), simply incrementing
//                the current_index takes care of fulfilling the
//                postcondition for the function for both of the two
//                possible scenarios (current item is and is not the
//                last item in the sequence).

#include <cassert>
#include "Sequence.h"
#include <iostream>
using namespace std;

namespace CS3358_FA2023
{
   // CONSTRUCTORS and DESTRUCTOR
   sequence::sequence(size_type initial_capacity) : capacity(initial_capacity), 
                                                   used(0), current_index(0)
   {
      //Checks if initial capacity is valid.
      if(initial_capacity < 1){
         capacity = 1;
      }

      //Creates a new dynamically allocated array.
      data = new value_type[capacity];
   }

   sequence::sequence(const sequence& source) : capacity(source.capacity), 
                                                used(source.used), 
                                                current_index(source.current_index)
   {
      //Creates a new dynamically allocated array.
      data =  new value_type[capacity];

      //Copies all of the data into the source.data array
      for( size_type i = 0; i < used; ++i){
         data[i] = source.data[i];
      }
   }

   sequence::~sequence()
   {
      //Deallocates array.
      delete [] data;
      data = NULL;
   }

   // MODIFICATION MEMBER FUNCTIONS
   void sequence::resize(size_type new_capacity)
   {
      //Checks if new_capacity is valid. If its not then change 
      //capacity to correct value.
      if(new_capacity < 1){
         capacity = 1;
      }

      else if(new_capacity < used){
         capacity = used;
      }

      else{
         capacity = new_capacity;
      }

      //Creates a new dynamically alloacted array 
      //based on the new capacity.
      value_type* temp_data = new value_type[capacity];

      //Copies the data into a new array.
       for(size_type i = 0; i < used; i++){
       temp_data[i] = data[i];
   }

      //Deallocates the array.
      delete [] data;
      data = temp_data;
   }

   void sequence::start()
   {
      //Sets the current index to 0.
      if(used !=0){
         current_index = 0;
      }
   }

   void sequence::advance()
   {
      //Assert checks if there is a valid current item.
      assert(is_item());

      //Changes the current_index to the 
      //next value in the array.
      current_index = current_index + 1;
   }

   void sequence::insert(const value_type& entry)
   {
      //Calls resize to resize the array to make 
      //room for another item.
      if(used == capacity){
         resize(size_type(1.5 * capacity) + 1);
      }

      //Checks if is_item is valid. If not then set 
      //current_index to 0.
      if(is_item() == false){
         current_index = 0;

      //Shifts all the items in the array to accomodate 
      //for the new entry.
         for (size_type i = used + 1; i > current_index; --i){
            data[i] = data[i - 1];
         }
         
         //Add entry to the begining of the array.
         data[current_index] = entry;
         ++used;
      }

      else{

         //Shifts all the items in the array to 
         //accomodate for the new entry.
         for(size_type i = used +1; i > current_index; --i){
            data[i] = data[i-1];
         }

         //Add entry before the past current_index
         data[current_index] = entry;
         ++used;
      }
   }

   void sequence::attach(const value_type& entry)
   {
      //Calls resize to resize the array to make
      // room for another item.
      if(used == capacity){
         resize(size_type(1.5 * capacity) + 1);
      }

      //Checks if is_item is valid. If not then add 
      //entry at the end of the array.
      if(is_item() == false){
         data[current_index] = entry;
         used++;
      }

      else{
         //Changes  current_index into the next value.
         current_index = current_index +1;

         //Shifts all the items in the array to 
         //accomodate for the new entry.
         for(size_type i = used +1; i > current_index; --i){
            data[i] = data[i-1];
      }

      //Add entry after the past current_index.
      data[current_index] = entry;
         used++;
      }
   }

   void sequence::remove_current()
   {
      //Assert checks if there is a valid current item.
      assert(is_item());

      //Removes current item by shifting
      // all the items to the left.
      for(size_type i = current_index; i < used - 1; i++){ 
         data[i] = data[i + 1];
      }

      //Updates used.
      --used;

   }

   sequence& sequence::operator=(const sequence& source)
   {
      //Checks if the invoking object is NOT equal to source.
      if(this != &source){

         //Creates a new dynamic array.
         value_type* newData = new value_type[source.capacity];

         //Copies source data into the new array.
         for(size_type i = 0; i <= source.used; i++){
            newData[i] = source.data[i];
         }

         //Deallocate old dynamic array.
         delete [] data;

         //Updates the data/capacity/used/current_index.
         data = newData;
         capacity = source.capacity;
         used = source.used;
         current_index = source.current_index;

      }
      return *this;
   }

   // CONSTANT MEMBER FUNCTIONS
   sequence::size_type sequence::size() const
   {
      //Returns the number in used which is the number
      //of elements in the array.
      return used;
   }

   bool sequence::is_item() const
   {
      //Checks if the current_index is a 
      //valid member of the array.
      if(current_index != used){
         return true;
      }
      return false;
   }

   sequence::value_type sequence::current() const
   {
      //Checks if the current_index is valid.
      assert(is_item());

      //Returns the item in the spot of the current_index.
      return data[current_index];
   }
}
