#include <iostream>

class Movielist;
class Catalog;
class date;
struct nodemov;
struct nodecat;

using namespace std;

class date
{
public:
    int month;
    int day;
    int year;
    bool valid = false;
    
    //default constructor
    date(){
    }
    
    //constructor make a date out of the day, month, and year inputted if it is valid
    date(int m, int d, int y){
        //checking if date is valid for jan, march, may, july, aug, oct, dec
        //they all have 31 days
        if((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && d >= 1 && d <= 31){
            month = m;
            day = d;
            year = y;
            valid = true;
        }
        //checking if the date is valid for feb
        else if(m == 2 && d >= 1 && d <= 29){
            if(d == 29 && y%4 != 0){
                //if the year is not divisible by 4, then it is not a leap year, so the 29th is invalid
                cout << "Date is invalid" << endl;
                return;
            }
            else{
                month = m;
                day = d;
                year = y;
                valid = true;
            }
        }
        //checking if the date is valid for april, june, sept, nov
        //they all have 30 days
        else if((m == 3 || m == 6 || m == 9 || m == 11) && d >= 1 && d <= 30){ //checking if the date is valid for March
            month = m;
            day = d;
            year = y;
            valid = true;
        }
        else{
            //cout << "Date is invalid" << endl;
        }
    }
    
    //if the date is not valid, it will notify the user when they try to print also
    //This function will print the date
    void printdate(){
        if(valid){
            cout << month << "/" << day << "/" << year;
        }
        else{
            cout << "Date is invalid" << endl;
        }
    }
    
    //a date is inputted, and if the date called on is before the inputted date, then it will return true.
    //if it is after the inputted date, it is false.
    bool before(date d){
        //if the year is smaller, its before.
        if(year < d.year){
            return true;
        }
        //if the year is not smaller, check equal to
        else if(year == d.year){
            //same year, check month
            if(month < d.month){
                return true;
            }
            //same month, check day
            else if(month == d.month){
                if(day < d.day){
                    return true;
                }
            }
            //same year, but date is after.
            else return false;
        }
        //any other case, it is after.
        return false;
    }
    
};

//These nodes will be for the movies
struct nodemov
{
    string title; //title of the movie
    nodemov* next; //pointer to the next movie in the list
    nodemov* prev; //pointer to the previous movie in the list
    bool ishead = false; //the first movie in the list will be true, ishead acts as a flag
    date d; //the date the movie was uploaded, indicated when the movie is inserted
    
    //nodecat* cat;
    
    //ASK ABOUT THIS, HOW CAN I GET THE MOVIES TO POINT TO A CATEGORY

    
    //default constructor
    nodemov(){
    }
    
    //constructor for title, month, day, and year included
    nodemov(string movietitle, int month, int day, int year){
        d = date(month, day, year);
        if(d.valid){
            title = movietitle;
            next = NULL;
            prev = NULL;
            ishead = false;
        }
        else{
            cout << "Date invalid, please try again." << endl;
        }
    }
    
    //constructor when the title and the date is given in this form.
    nodemov(string movietitle, date moviedate){
        //if the date is not valid, the movie is not added.
        d = moviedate;
        if(!d.valid){
            cout << "The date is not valid, movie cannot be added" << endl;
            return;
        }
        title = movietitle;
        next = NULL;
        prev = NULL;
        ishead = false;
    }
};

//These nodes will be for the categories
struct nodecat
{
    string name; //name of the category
    nodecat* prev; //pointer to the previous category
    nodecat* next; //pointer to the next category
    Movielist* movies; //pointer to a movie list
    
    //default constructor
    nodecat(){
    }
    
    //constructor with the name of the category
    nodecat(string catname){
        name = catname;
        prev = NULL;
        next = NULL;
        movies = NULL;
    }
};


class Movielist{
private:
    nodemov* head;
    nodemov* tail;
    int nummovs;
    
public:
    Movielist(){
        head = NULL;
        tail = NULL;
        nummovs = 0;
    }
    
    
    
    //add movie in alphabetical order. need title and date, check if there exists a movie of the same title already.
    void addmov(string moviename, date moviedate){
        //make a new movie node with the name, and date
        nodemov* temp = new nodemov(moviename, moviedate);
        
        //if the movie list is empty, then we will add the movie node, and make it the head and tail of the movie list.
        if(head == NULL){
            temp->ishead = true;
            
            head = temp;
            tail = temp;
            tail->next = head;
            head->prev = tail;
            nummovs += 1;
            //cout << temp->title << " has been added" << endl;
        }
        else{
            //if the movie is already in the list, it won't add it. This is a search.
            nodemov* cur = head;
            
            //case where it is the first one.
            if(temp->title == head->title){
                cout << temp->title << " is already in the list" << endl;
                return;
            }
            //this will check the rest of the movies until we get back to head.
            for(cur = head->next; cur != head; cur = cur->next){
                //if the movie is already in the list, then don't add it.
                if(temp->title == cur->title){
                    //if the current name is equal to the one we are searching for, return current.
                    cout << temp->title << " is already in the list" << endl;
                    return;
                }
            }
            

            //if the movie would be inserted at the beginning of the list
            if(temp->title < head->title){
                temp->next = head;
                head->ishead = false;
                temp->ishead = true;
                head->prev = temp;
                head = temp;
                head->prev = tail;
                tail->next = head;
                nummovs += 1;
                
                //cout << temp->title << " has been inserted at the beginning"<< endl;
            }
            
            //inserting anywhere else in order.
            else{
                nodemov* cur = head;
                //for inserting at the middle of the list
                while(cur->next != head && cur->next->title < temp->title){
                    cur = cur->next;
                }
                temp->next = cur->next;
                cur->next = temp;
                temp->next->prev = temp;
                temp->prev = cur;
                //cout << temp->title << " has been inserted in order" << endl;
                
                //if the node we inserted was at the end of the list.
                if(temp->next == head){
                    tail = temp;
                    tail->next = head;
                }
                nummovs += 1;
            }
        }
    }
    
    //deletes movie of the title given.
    void delmov(string title){
        //if the movie list is empty
        if(head == NULL){
            cout << "There are no movies to remove" << endl;
            return;
        }
        //if the movie we need to delete is at the front of the list
        if(head->title == title){
            head->next->ishead = true;
            head->next->prev = tail;
            tail->next = head->next;
            head = head->next;
            nummovs -= 1;
            return;
        }
        
        //if the movie we need to delete is at the end of the list
        if(tail->title == title){
            tail->prev->next = head;
            head->prev = tail->prev;
            tail = tail->prev;
            nummovs -= 1;
            return;
        }
        
        //if the movie we need to delete is in the middle of the list
        nodemov* cur = head;
        for(cur = head->next; cur->next != head; cur = cur->next){
            if(cur->title == title){
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                nummovs -=1;
                return;
            }
        }
        
    }
    
    //return the head to the list of movies
    nodemov* gethead(){
        return head;
    }
    
    //return the tail of the list of movies
    nodemov* gettail(){
        return tail;
    }
    
    //returns the number of movies in a list
    int getnummovs(){
        return nummovs;
    }
    
    //prints each movie given the head of a movie list.
    void printmovies(nodemov* a){
        //if the list is empty, it will tell you.
        if(head == NULL){
            cout << "The list is empty" << endl;
            return;
        }
        else{
            //it will list each title until we reach the last one.
            cout << a->title << ", ";
            if(a->next->ishead == true){
                cout << endl;
                return;
            }
            printmovies(a->next);
        }
    }
};




class Catalog{
private:
    nodecat* head;
    nodecat* tail;
    int numcats;
    
public:
    //default catalog
    Catalog(){
        head = NULL;
        tail = NULL;
        numcats = 0;
    }
    
    //return the head to the list of categories
    nodecat* gethead(){
        return head;
    }
    
    //return the tail of the list of categories
    nodecat* gettail(){
        return tail;
    }
    
    //returns the number of categories
    int getnumcats(){
        return numcats;
    }
    
    //adds a category to the list of categories
    void addcat(string name){
        nodecat* temp = new nodecat(name);
        
        //if the list is empty, we will have that category be the head and tail.
        if(head == NULL){
            head = temp;
            tail = temp;
        }
        
        //if the list is not empty, then add it to the end.
        else{
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
        
        //increase number of catregories by 1.
        numcats += 1;
    }
    
    //deletes a category given its name.
    void delcat(string name){
        //if the movie list is empty
        if(head == NULL){
            cout << "There are no categories to remove" << endl;
            return;
        }
        //if the cat we need to delete is at the front of the list
        if(head->name == name){
            head = head->next;
            numcats -= 1;
            return;
        }
        
        //if the movie we need to delete is at the end of the list
        if(tail->name == name){
            tail = tail->prev;
            tail->next = NULL;
            numcats -= 1;
            return;
        }
        
        //if the movie we need to delete is in the middle of the list
        nodecat* cur = head;
        for(cur = head->next; cur->next != NULL; cur = cur->next){
            if(cur->name == name){
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
                numcats -=1;
                return;
            }
        }
    }
    
    //searches the categories with inputted category name
    //returns a pointer to the category or a null pointer.
    nodecat* search(string catname){
        //make a pointer to the head of the list of categories
        nodecat* cur = head;
        
        //will check all categories until cur == NULL
        for(cur = head; cur != NULL; cur = cur->next){
            //cout << cur->name << " is being checked" << endl;
            if(cur->name == catname){
                //if the current name is equal to the one we are searching for, return current.
                //cout << cur->name << " has been found" << endl;
                return cur;
            }
        }
        //if it was not found in the for loop, it will return a nullptr and say that it was not found.
        cout << "The category was not found" << endl;
        return NULL;
    }
    
    //adds a movie of a given title, category, and date to the category given.
    void addmovtocat(string title, string category, date d){
        //search for the category, and if it is not there, give an error.
        nodecat* cat = search(category);
        if(cat == NULL){
            cout << "This category does not exist" << endl;
            return;
        }
        
        //if the movie list is null, make a new movie list
        if(cat->movies == NULL){
            cat->movies = new Movielist();
        }
        
        cat->movies->addmov(title, d);
    }
    
    //print all movies. input a pointer to the category.
    void printmoviesincat(nodecat* cat){
        if(cat == NULL){
            return;
        }
        //will use the print movies function in the MovieList class. Need to give it the head of the movie list, which is cat->movies->head
        cout << "[" << cat->name << "] ";
        cat->movies->printmovies(cat->movies->gethead());
    }
    
    //binary search within a category. Give the category, the title of the movie being searched, the lowest index (0) and the highest index (number of movies in that category.
    int searchmovincat(nodecat* cat, string title, int low, int high){
        //if the list is empty, then it will return false.
        if(cat->movies == NULL){
            cout << "The category does not exist" << endl;
            return false;
        }
        int mid;
        //set middle to the head of the movies list, then we will adjust it later.
        nodemov* middle = cat->movies->gethead();
        bool found = false;
        //if the low index is greater than high, then it will return false.
        if(low > high){
            found = false;
        }
        else {
            mid = (low + high) / 2;
            //use a for loop to get to the middle index
            for(int i = 0; i < mid; i++){
                middle = middle->next;
            }
            //if the movie I am looking for is the middle index, return found
            if(middle->title == title ){
                found = true;
            }
            else{
                //if the movie is not the middle index
                //do a binary search on the lower half of the list or the upper half.
                if(middle->title < title){
                    found = searchmovincat(cat, title, mid + 1, high);
                }
                else{
                    found = searchmovincat(cat, title, low, mid - 1);
                }
            }
        }
        return found;
    }
    
    //returns the movie index. Uses a pointer to the category and the title as inputs.
    int getmovieindex(nodecat* cat, string title){
        //if the movie list is empty, the movie has no index
        if(cat->movies == NULL){
            cout << "There are no movies in this category" << endl;
            return NULL;
        }
        nodemov* cur = cat->movies->gethead();
        //if the movie is in the list, it will return the index
        for(int i = 0; i < cat->movies->getnummovs(); i++){
            if(cur->title == title){
                cout << "The index of " << title << " is: " << i << endl;
                return i;
            }
            cur = cur->next;
        }
        //if the movie is not in the list, return NULL for the index.
        cout << "The movie was not found"<< endl;
        return NULL;
    }
    
    //searches all the movies for a inputted title.
    bool searchallmovs(string title){
        //start at the first category
        nodecat* curcat = head;
        while(curcat != NULL){
            //use the binary search on that category, and if it is true, then it will print that it was found.
            if(searchmovincat(curcat, title, 0, curcat->movies->getnummovs())){
                cout << title << " was found in the category: " << curcat->name << endl;
                return true;
            }
            //check the next category, until we run out of categories.
            curcat = curcat->next;
        }
        //If the binary search is false for all the categories, then it will tell the user it was not found.
        cout << title << " was not found" << endl;
        return false;
    }
    
    //prints all movies in Netflix
    void printallmovs(){
        //start at the first category
        nodecat* curcat = head;
        while(curcat != NULL){
            printmoviesincat(curcat);
            curcat = curcat->next;
        }
    }
    
    //deletes all movies before a certain date that is given.
    void delmovsbefore(date d){
        //pointers for the category and movie that is being checked.
        nodecat* curcat;
        nodemov* curmov;
        //for loop for going through the categories until I reach the end NULL
        for(curcat = head; curcat != NULL; curcat = curcat->next){
            //for loop for going through the movies in each category, deletes if the date of the move is before the date input by user.
            //if the movie we need to delete is the head
            if(curcat->movies->gethead()->d.before(d)){
                cout << curcat->movies->gethead()->title << " has been deleted" << endl;
                curcat->movies->delmov(curcat->movies->gethead()->title);
            }
            for(curmov = curcat->movies->gethead()->next; !curmov->ishead; curmov = curmov->next){
                if(curmov->d.before(d)){
                    cout << curmov->title << " has been deleted" << endl;
                    curcat->movies->delmov(curmov->title);
                }
            }
        }
    }
    
};




int main() {
    //make a catalog with the name Netflix
    Catalog Netflix;
    
    //creating all the categories
    Netflix.addcat("children");
    Netflix.addcat("action");
    Netflix.addcat("comedy");
    Netflix.addcat("romance");
    Netflix.addcat("horror");
    
    //creating movie list for children category
    Netflix.addmovtocat("Barbie", "children", date(10,23,2001));
    Netflix.addmovtocat("Lion King", "children", date(6,24,1994));
    Netflix.addmovtocat("Harry Potter", "children", date(11,14,2001));
    Netflix.addmovtocat("Frozen", "children", date(11,27,2013));
    Netflix.addmovtocat("Matilda", "children", date(7,28,1996));
    
    //creating movie list for action category
    Netflix.addmovtocat("Taken", "action", date(1,30,2009));
    Netflix.addmovtocat("MI 5", "action", date(5,13,2002));
    Netflix.addmovtocat("Rocky", "action", date(11,21,1976));
    Netflix.addmovtocat("Black Widow", "action", date(7,9,2021));
    Netflix.addmovtocat("Star Wars", "action", date(5,25,1977));
    
    //creating movie list for comedy category
    Netflix.addmovtocat("Grown Ups", "comedy", date(6,25,2010));
    Netflix.addmovtocat("Harold & Kumar", "comedy", date(7,30,2004));
    Netflix.addmovtocat("Tuxedo", "comedy", date(9,27,2002));
    Netflix.addmovtocat("Jerry Maguire", "comedy", date(12,13,1996));
    
    //creating movie list for romance category
    Netflix.addmovtocat("Love Hard", "romance", date(11,5,2021));
    Netflix.addmovtocat("The Notebook", "romance", date(6,25,2004));
    Netflix.addmovtocat("Safe Haven", "romance", date(2,14,2013));
    Netflix.addmovtocat("The Titanic", "romance", date(12,19,1997));
    
    //creating movie list for horror category
    Netflix.addmovtocat("It", "horror", date(9,5,2017));
    Netflix.addmovtocat("The Conjuring", "horror", date(7,19,2013));
    Netflix.addmovtocat("Scream", "horror", date(12,20,1996));
    Netflix.addmovtocat("The Shallows", "horror", date(6,24,2016));
    
    //search a category by name. It will return a pointer to it if it exists, and a null pointer if it doesnt.
    cout << "------- SEARCH CATEGORY -------" << endl;
    cout << "The " << Netflix.search("action")->name << " category was found " << endl;
    Netflix.search("thriller");
    cout << endl;
    
    //printing all the movies
    cout << "------- PRINTING ALL MOVIES -------" << endl;
    Netflix.printallmovs();
    cout << endl;
    
    //printing all movies in a category
    cout << "------- PRINTING ALL MOVIES IN A CATEGORY -------" << endl;
    //input the pointer to the category, using search function
    Netflix.printmoviesincat(Netflix.search("romance"));
    cout << endl;
    
    //showing that you cannot add a movie with an invalid date, or a movie that it already in the list.
    cout << "------- ADDING MOVIE CONDITIONS TEST -------" << endl;
    Netflix.addmovtocat("Dune", "action", date(2,29,2003));
    Netflix.addmovtocat("Star Wars", "action", date(5,25,1977));
    cout << endl;
    
    
    //binary search within category
    cout << "------- SEARCHING MOVIES IN CAT WITH BINARY SEARCH -------" << endl;
    //search the movies in the category using the pointer to the category of your choosing (using search function)
    //if it is true, say the movie was found, if false, say it was not.
    //using ternary operator.
    cout << (Netflix.searchmovincat(Netflix.search("children"), "Lion King", 0, Netflix.search("children")->movies->getnummovs()) ? "Lion King was found" : "Lion King was not Found") << endl;
    
    cout << (Netflix.searchmovincat(Netflix.search("action"), "Rocky", 0, Netflix.search("action")->movies->getnummovs()) ? "Rocky was found" : "Rocky was not Found") << endl;
    
    cout << (Netflix.searchmovincat(Netflix.search("comedy"), "Harold & Kumar", 0, Netflix.search("comedy")->movies->getnummovs()) ? "Harold & Kumar was found" : "Harold & Kumar was not Found") << endl;
    cout << endl;
    
    //get the movie index
    cout << "------- GETTING THE MOVIE INDEX -------" << endl;
    Netflix.getmovieindex(Netflix.search("children"), "Frozen");
    Netflix.getmovieindex(Netflix.search("comedy"), "Tuxedo");
    cout << endl;
    
    //search a movie by name when we dont know the category. Returns true or false.
    cout << "------- SEARCH MOVIE WITHOUT CATEGORY -------" << endl;
    Netflix.searchallmovs("The Shallows");
    Netflix.searchallmovs("FAKE MOVIE");
    cout << endl;
    
    //removing a category and all the movies in it
    cout << "------- REMOVING A CATEGORY -------" << endl;
    Netflix.delcat("action");
    cout << "after deleting action category: " << endl;
    Netflix.printallmovs();
    cout << endl;
    
    //removing all movies before 1,1,2000
    cout << "------- REMOVING ALL MOVIES OLDER THAN (BEFORE) 2000 -------" << endl;
    Netflix.delmovsbefore(date(1,1,2000));
    //will delete Lion King, Matilda, Jerry Maguire, The Titanic, Scream
    cout << endl << "After deleting the movies before 2000: " << endl;
    Netflix.printallmovs();
    cout << endl;
    
    
    return 0;
}
