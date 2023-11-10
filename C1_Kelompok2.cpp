#include <iostream>  // fungsi input & output
#include <string>    // fungsi manipulasi string
#include <conio.h>   // fungsi input/output khusus konsol
#include <stdexcept> // kelas pengecualian standar
#include <cmath>     // fungsi matematika dalam akar kuadrat searching
#include <limits>
using namespace std;

// Definisi Struktur Data
struct Review
{ // menyimpan ulasan user terkait lokasi wisata
    string review;
    Review *next;
};

struct TouristLocation
{ // menyimpan informasi lokasi wisata
    int id;
    string name;
    string description;
    double rating;
    Review *reviews;
    TouristLocation *next;
};

struct UserAccount
{ // menyimpan informasi akun user
    string username;
    string password;
    UserAccount *next;
};

// pointer global ke head linked list
TouristLocation *locationHead = NULL;
UserAccount *userAccountsHead = NULL;

// deklarasi fungsi
void login();
void adminMenu();
void userMenu();
void displayUserMenu();
void adminLogin();
void addLocationFirst();
void addLocationMiddle();
void addLocationLast();
void updateLocation();
void deleteLocationFirst();
void deleteLocationMiddle();
void deleteLocationLast();
void displayLocations();
void userLogin();
void registerUser();
void viewLocation();
void addReview();
void searching();
void pushReview(Review *&stackTop, const string &reviewText);

// variabel global untuk menyimpan user yang sedang login
string savedUsername = "";
string savedPassword = "";

// fungsi login user
void userLogin()
{
    string inputUsername, inputPassword;
    bool loginSuccess = false;

    // meminta user memasukkan nama pengguna dan kata sandi
    cout << "Enter username: ";
    cin >> inputUsername;
    cout << "Enter password: ";
    cin >> inputPassword;

    // periksa apakah akun pengguna dan kata sandi ada dalam daftar akun pengguna
    UserAccount *temp = userAccountsHead;
    while (temp != NULL)
    {
        if (temp->username == inputUsername && temp->password == inputPassword)
        {
            cout << "Login successful. Welcome, " << inputUsername << "!" << endl;
            loginSuccess = true;
            break;
        }
        temp = temp->next;
    }
    // jika login tidak berhasil
    if (!loginSuccess)
    {
        cout << "Login failed. Incorrect username or password." << endl;
        cout << "Press Enter to return to the main menu...";
        getch();
        system("cls");
        return;
    }

    // Simpan nama pengguna yang berhasil login untuk digunakan di seluruh aplikasi
    savedUsername = inputUsername;

    cout << "Press Enter to go to the user menu...";
    getch();
    system("cls");
    userMenu();
}

// fungsi registrasi user
void registerUser()
{
    string newUsername, newPassword;
    // meminta user memasukkan username baru
    cout << "Enter a new username: ";
    cin >> newUsername;

    // Periksa apakah username sudah ada di dalam daftar akun pengguna
    UserAccount *temp = userAccountsHead;
    while (temp != NULL)
    {
        if (temp->username == newUsername)
        { // tampilan pesan kesalahan apabila username sudah digunakan
            cout << "Username already in use. Please choose another username." << endl;
            cout << "Press Enter to go back to the user menu...";
            getch();
            return;
        }
        temp = temp->next;
    }
    // meminta user memasukkan password baru
    cout << "Enter a new password: ";
    cin >> newPassword;

    // Buat node baru untuk akun pengguna
    UserAccount *newUser = new UserAccount;
    newUser->username = newUsername;
    newUser->password = newPassword;
    newUser->next = userAccountsHead;
    userAccountsHead = newUser;
    // Pesan setelah registrasi berhasil
    cout << "Registration successful. Welcome, " << newUser->username << "!" << endl;
    cout << "Press Enter to go to the user menu...";
    getch();
}

// fungsi tampilan menu user
void displayUserMenu()
{
    string userChoiceStr;
    do
    {
        system("cls");
        cout << "==============================" << endl;
        cout << "|          WELCOME           |" << endl;
        cout << "==============================" << endl;
        cout << "| Options:                   |" << endl;
        cout << "| 1) User Login              |" << endl;
        cout << "| 2) Register User           |" << endl;
        cout << "| 3) Return to Main Menu     |" << endl;
        cout << "==============================" << endl;
        cout << "Enter choice (1-3): ";
        cin >> userChoiceStr;
        cout << "==============================" << endl;

        try
        { // konversi  pilhan user menjadi angka
            int userChoice = stoi(userChoiceStr);
            // memproses pilihan user
            switch (userChoice)
            {
            case 1:
                userLogin();
                break;
            case 2:
                registerUser();
                break;
            case 3:
                return;
            default: // pesan kesalahan untuk pilihan tidak valid
                cout << "Invalid choice. Please enter a valid option." << endl;
                cout << "Press Enter to return to the User Menu...";
                getch();
                break;
            }
        }
        catch (const invalid_argument &e)
        {
            // pesan kesalahan untuk input tidak valid
            cout << "Invalid input. Please enter a valid option (1-3)." << endl;
            cout << "Press Enter to continue...";
            getch();
        }

    } while (true);
}

// Fungsi Login Admin
void adminLogin()
{
    int attempts = 0;
    string adminUsername = "admin";
    string adminPassword = "admin";

    do
    {
        // meminta admin menginput username dan password admin
        string enteredUsername, enteredPassword;
        cout << "Enter Admin Username: ";
        cin >> enteredUsername;
        cout << "Enter Admin Password: ";
        cin >> enteredPassword;
        // memeriksa kecocokan username dan password
        if (enteredUsername == adminUsername && enteredPassword == adminPassword)
        {
            system("cls"); // pesan tampilan login sukses
            cout << "Admin login successful!" << endl;
            cout << "Press Enter to go to the admin menu...";
            getch();
            adminMenu();
            return;
        }
        else
        { // menampilkan pesan gagal login dan mencatat jumlah percobaan
            attempts++;
            cout << "Login failed. Invalid username or password. (" << attempts << " attempts)" << endl;
            // memeriksa apakah jumlah percobaan melebihi batas
            if (attempts >= 3)
            {
                cout << "Exceeded maximum login attempts. Please try again later." << endl;
                return;
            }
        }
    } while (true);
}

// fungsi metode merge sort berdasarjan ID
void merge(TouristLocation *locations[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // membuat array sementara
    TouristLocation *leftArr[n1];
    TouristLocation *rightArr[n2];

    // menyalin data ke array sementara leftArr[] dan rightArr[]
    for (int i = 0; i < n1; i++) {
        leftArr[i] = locations[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = locations[mid + 1 + j];
    }

    // menggabungkan kembali array sementara ke locations[left..right]
    int i = 0;    // indeks awal subarray pertama
    int j = 0;    // indeks awal subarray kedua
    int k = left; // indeks awal subarray yang digabungkan

    while (i < n1 && j < n2) {
        if (leftArr[i]->id <= rightArr[j]->id) { // mengubah kondisi untuk mengurutkan berdasarkan ID
            locations[k] = leftArr[i];
            i++;
        } else {
            locations[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // menyalin elemen-elemen yang tersisa dari leftArr[], jika ada
    while (i < n1) {
        locations[k] = leftArr[i];
        i++;
        k++;
    }

    // menyalin elemen-elemen yang tersisa dari rightArr[], jika ada
    while (j < n2) {
        locations[k] = rightArr[j];
        j++;
        k++;
    }
}

// fungsi mergeSort untuk mengurutkan lokasi wisata berdasarkan ID
void mergeSort(TouristLocation *locations[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // mengurutkan setengah pertama dan setengah kedua
        mergeSort(locations, left, mid);
        mergeSort(locations, mid + 1, right);

        // menggabungkan setengah-setengah yang telah diurutkan
        merge(locations, left, mid, right);
    }
}

// fungsi untuk mengurutkan lokasi wisata berdasarkan ID menggunakan jump search
void sortLocationsByID() {
    if (locationHead == NULL) {
        cout << "No Data Found. Cannot Sorting." << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    // mengonversi linked list dari lokasi wisata ke dalam array untuk diurutkan
    TouristLocation *currentLocation = locationHead;
    int count = 0;
    while (currentLocation != NULL) {
        count++;
        currentLocation = currentLocation->next;
    }

    // membuat array untuk menyimpan lokasi wisata
    TouristLocation *locations[count];
    currentLocation = locationHead;
    for (int i = 0; i < count; i++) {
        locations[i] = currentLocation;
        currentLocation = currentLocation->next;
    }
    // Melakukan merge sort pada array
    mergeSort(locations, 0, count - 1);

    // Membangun kembali linked list dari array yang telah diurutkan
    locationHead = locations[0];
    for (int i = 0; i < count - 1; i++) {
        locations[i]->next = locations[i + 1];
    }
    locations[count - 1]->next = NULL;

    cout << "Tourist Locations sorted by ID successfully!" << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

// fungsi menu admin
void adminMenu() {
    string choiceStr;
    while (true)
    {
        system("cls");
        cout << " Welcome admin " << endl;
        cout << "========================================" << endl;
        cout << "|             ADMIN MENU               |" << endl;
        cout << "========================================" << endl;
        cout << "| 1.  Add Tourist Location First       |" << endl;
        cout << "| 2.  Add Tourist Location Middle      |" << endl;
        cout << "| 3.  Add Tourist Location Last        |" << endl;
        cout << "| 4.  Update Tourist Location          |" << endl;
        cout << "| 5.  Delete Tourist Location First    |" << endl;
        cout << "| 6.  Delete Tourist Location Middle   |" << endl;
        cout << "| 7.  Delete Tourist Location Last     |" << endl;
        cout << "| 8.  Display Tourist Locations        |" << endl;
        cout << "| 9.  Sort Tourist Locations by ID     |" << endl;
        cout << "| 10. Logout                           |" << endl;
        cout << "========================================" << endl;
        cout << "Enter your choice (1-10): ";
        cin >> choiceStr;
        cout << "========================================" << endl;

        try
        {
            int choice = stoi(choiceStr);

            switch (choice)
            {
            case 1:
                addLocationFirst();
                break;
            case 2:
                addLocationMiddle();
                break;
            case 3:
                addLocationLast();
                break;
            case 4:
                updateLocation();
                break;
            case 5:
                deleteLocationFirst();
                break;
            case 6:
                deleteLocationMiddle();
                break;
            case 7:
                deleteLocationLast();
                break;
            case 8:
                displayLocations();
                break;
            case 9:
                sortLocationsByID();
                break;
            case 10:
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                cout << "Press Enter to continue...";
                getch();
                break;
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid input. Please enter a valid option (1-10)." << endl;
            cout << "Press Enter to continue...";
            getch();
        }
    }
}

// fungsi untuk memasukkan dan memvalidasi rating
double inputAndValidateRating()
{
    while (true)
    {
        string ratingInput;
        cout << "Enter Location Rating (1-5): ";
        getline(cin, ratingInput);

        try
        {
            double rating = stod(ratingInput);
            if (rating >= 1.0 && rating <= 5.0)
            {
                return rating;
            }
            else
            {
                cout << "Invalid rating. Please enter a rating between 1 and 5." << endl;
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid rating format. Please enter a valid number." << endl;
        }
    }
}

// fungsi untuk menambahkan lokasi wisata di awal
void addLocationFirst()
{
    TouristLocation *newLocation = new TouristLocation;
    cin.ignore();

    int newID;
    while (true)
    {
        cout << "Enter Location ID: ";
        if (cin >> newID && newID >= 0) // Validasi ID tidak boleh negatif
        {
            break; // Keluar dari loop jika input adalah angka dan tidak negatif
        }
        else
        {
            cout << "Invalid input. Please enter a non-negative numeric ID." << endl;
            cin.clear(); // Reset status error cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer
        }
    }

    newLocation->id = newID; // Menambahkan input ID lokasi

    // Memasukkan input nama dan deskripsi lokasi
    cout << "Enter Location Name: ";
    cin.ignore();
    getline(cin, newLocation->name);

    cout << "Enter Location Description: ";
    getline(cin, newLocation->description);

    // Memasukkan input rating lokasi
    newLocation->rating = inputAndValidateRating();

    // Sisipkan lokasi baru di awal
    newLocation->reviews = NULL;
    newLocation->next = locationHead;
    locationHead = newLocation;

    cout << "Tourist Location added successfully at the beginning!" << endl;
    cout << "Press Enter to continue...";
    getch();
}

// fungsi untuk menambahkan lokasi wisata di tengah
void addLocationMiddle()
{
    TouristLocation *newLocation = new TouristLocation;

    int newID;
    while (true)
    {
        cout << "Enter Location ID: ";
        if (cin >> newID && newID >= 0)
        {
            break; // keluar dari loop jika input adalah angka
        }
        else
        {
            cout << "Invalid input. Please enter a numeric ID." << endl;
            cin.clear(); // reset status error cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan buffer
        }
    }

    newLocation->id = newID; // menambahkan input ID lokasi

    cin.ignore();
    cout << "Enter Location Name: ";
    getline(cin, newLocation->name); // memasukkan input nama lokasi

    cout << "Enter Location Description: ";
    getline(cin, newLocation->description); // memasukkan input deskripsi lokasi

    newLocation->rating = inputAndValidateRating(); // memasukkan input rating lokasi

    cout << "Enter ID after which you want to add this location: ";
    int targetID;
    cin >> targetID; // meminta ID setelah lokasi mana lokasi baru harus disisipkan

    // cari posisi lokasi berdasarkan ID target
    TouristLocation *currentLocation = locationHead;
    while (currentLocation != NULL)
    {
        if (currentLocation->id == targetID)
        {
            // Menyisipkan lokasi baru di tengah
            newLocation->reviews = NULL;
            newLocation->next = currentLocation->next;
            currentLocation->next = newLocation;

            cout << "Tourist Location added successfully after Location with ID " << targetID << "!" << endl;
            cout << "Press Enter to continue...";
            getch();
            return;
        }
        currentLocation = currentLocation->next;
    }

    cout << "Location with ID " << targetID << " not found. Unable to add the location." << endl;
    cout << "Press Enter to continue...";
    getch();
}
// fungsi untuk menambahkan lokasi wisata di akhir
void addLocationLast()
{
    TouristLocation *newLocation = new TouristLocation;
    cin.ignore();

    int newID;
    while (true)
    {
        cout << "Enter Location ID: ";
        if (cin >> newID && newID >= 0)
        {
            break; // keluar dari loop jika input adalah angka
        }
        else
        {
            cout << "Invalid input. Please enter a numeric ID." << endl;
            cin.clear(); // reset status error cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan buffer
        }
    }

    newLocation->id = newID; // menambahkan input ID lokasi

    cout << "Enter Location Name: ";
    cin.ignore();
    getline(cin, newLocation->name);

    cout << "Enter Location Description: ";
    getline(cin, newLocation->description); // menambahkan input deskripsi lokasi

    // sisipkan lokasi baru di akhir
    newLocation->rating = inputAndValidateRating();
    newLocation->reviews = NULL;
    newLocation->next = NULL;

    if (locationHead == NULL)
    {
        locationHead = newLocation;
    }
    else
    {
        TouristLocation *currentLocation = locationHead;
        while (currentLocation->next != NULL)
        {
            currentLocation = currentLocation->next;
        }
        currentLocation->next = newLocation;
    }

    cout << "Tourist Location added successfully at the end!" << endl;
    cout << "Press Enter to continue...";
    getch();
}

// fungsi update lokasi
void updateLocation()
{
    if (locationHead == NULL)
    {
        cout << "No Data Found. Cannot Update." << endl;
        cout << "Press Enter to continue...";
        cin.ignore(); // membersihkan buffer sebelum melanjutkan
        getch();
        return;
    }

    int locationID;
    while (true)
    {
        cout << "Enter the ID of the location to update: ";
        if (cin >> locationID && locationID >= 0)
        {
            break; // keluar dari loop jika input adalah angka
        }
        else
        {
            cout << "Invalid input. Please enter a numeric ID." << endl;
            cin.clear(); // reset status error cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan buffer
        }
    }

    TouristLocation *currentLocation = locationHead;

    while (currentLocation != NULL)
    {
        if (currentLocation->id == locationID)
        {
            cout << "Enter new Location Name: ";
            cin.ignore();
            getline(cin, currentLocation->name);

            cout << "Enter new Location Description: ";
            getline(cin, currentLocation->description);

            currentLocation->rating = inputAndValidateRating();

            cout << "Tourist Location with ID " << locationID << " updated successfully!" << endl;
            cout << "Press Enter to continue...";
            cin.ignore(); // membersihkan buffer sebelum melanjutkan
            getch();
            return;
        }

        currentLocation = currentLocation->next;
    }

    cout << "Location with ID " << locationID << " not found." << endl;
    cout << "Press Enter to continue...";
    cin.ignore(); // membersihkan buffer sebelum melanjutkan
    getch();
}

// menghapus lokasi wisata pertama
void deleteLocationFirst()
{
    if (locationHead == NULL)
    {
        cout << "No Data Found. Cannot Delete." << endl;
        cout << "Press Enter to continue...";
        getch();
        return;
    }

    TouristLocation *temp = locationHead;
    locationHead = locationHead->next;
    delete temp;

    cout << "First Tourist Location deleted successfully!" << endl;
    cout << "Press Enter to continue...";
    getch();
}

// fungsi untuk menghapus lokasi wisata di tengah daftar
void deleteLocationMiddle()
{
    if (locationHead == NULL || locationHead->next == NULL)
    {
        cout << "No Data Found. Cannot Delete." << endl;
        cout << "Press Enter to continue...";
        cin.ignore(); // membersihkan buffer sebelum melanjutkan
        getch();
        return;
    }

    int targetID;
    while (true)
    {
        cout << "Enter the ID of the location to delete: ";
        if (cin >> targetID && targetID >= 0)
        {
            break; // keluar dari loop jika input adalah angka
        }
        else
        {
            cout << "Invalid input. Please enter a numeric ID." << endl;
            cin.clear(); // reset status error cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bersihkan buffer
        }
    }

    TouristLocation *currentLocation = locationHead;
    TouristLocation *previousLocation = NULL;

    // cari lokasi yang akan dihapus
    while (currentLocation != NULL)
    {
        if (currentLocation->id == targetID)
        {
            if (previousLocation == NULL)
            {
                // jika lokasi yang akan dihapus berada di awal daftar
                locationHead = currentLocation->next;
            }
            else
            {
                // jika lokasi yang akan dihapus berada di tengah daftar
                previousLocation->next = currentLocation->next;
            }

            delete currentLocation;
            cout << "Tourist Location with ID " << targetID << " deleted successfully!" << endl;
            cout << "Press Enter to continue...";
            getch();
            return;
        }

        previousLocation = currentLocation;
        currentLocation = currentLocation->next;
    }

    cout << "Location with ID " << targetID << " not found." << endl;
    cout << "Press Enter to continue...";
    getch();
}

// fungsi untuk menghapus lokasi wisata terakhir
void deleteLocationLast()
{
    if (locationHead == NULL)
    {
        cout << "No Data Found. Cannot Delete." << endl;
        cout << "Press Enter to continue...";
        getch();
        return;
    }

    TouristLocation *currentLocation = locationHead;
    TouristLocation *previousLocation = NULL;
     // menelusuri hingga menemukan lokasi terakhir
    while (currentLocation->next != NULL)
    {
        previousLocation = currentLocation;
        currentLocation = currentLocation->next;
    }

    if (previousLocation == NULL)
    {   // jika hanya ada satu lokasi dan dihapus, set locationHead menjadi NULL
        delete locationHead;
        locationHead = NULL;
    }
    else
    {   // menghapus lokasi terakhir dan menetapkan next dari lokasi sebelumnya menjadi NULL
        delete currentLocation;
        previousLocation->next = NULL;
    }

    cout << "Last Tourist Location deleted successfully!" << endl;
    cout << "Press Enter to continue...";
    getch();
}
// menu user
void userMenu()
{
    string choiceStr;
    while (true)
    {
        system("cls");
        cout << "Welcome, " << savedUsername << endl;
        cout << "=====================================" << endl;
        cout << "|             USER MENU             |" << endl;
        cout << "=====================================" << endl;
        cout << "| 1. View Tourist Locations         |" << endl;
        cout << "| 2. Search Location by ID          |" << endl;
        cout << "| 3. Add Review                     |" << endl;
        cout << "| 4. Logout                         |" << endl;
        cout << "======================================" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choiceStr;
        cout << "======================================" << endl;

        try
        {
            int choice = stoi(choiceStr);

            switch (choice)
            {
            case 1:
                displayLocations();
                break;
            case 2:
                searching();
                break;
            case 3:
                addReview();
                break;
            case 4:
                cout << "Logging out..." << endl;
                return;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                cout << "Press Enter to continue...";
                getch();
                break;
            }
        }
        catch (const invalid_argument &e)
        {
            cout << "Invalid input. Please enter a valid option (1-4)." << endl;
            cout << "Press Enter to continue...";
            getch();
        }
    }
}

// fungsi menampilkan semua lokasi wisata
void displayLocations()
{
    TouristLocation *currentLocation = locationHead;

    if (locationHead == NULL)
    {
        cout << "No Data Found. Cannot Display." << endl;
        cout << "Press Enter to continue...";
        getch();
        return;
    }
    // Iterasi melalui setiap lokasi dan menampilkan informasi
    while (currentLocation != NULL)
    {
        cout << "Location ID: " << currentLocation->id << endl;
        cout << "Location Name: " << currentLocation->name << endl;
        cout << "Description: " << currentLocation->description << endl;
        cout << "Rating: " << currentLocation->rating << " / 5.0" << endl;

        // menampilkan ulasan jika ada
        Review *currentReview = currentLocation->reviews;
        if (currentReview != NULL)
        {
            cout << "Reviews:" << endl;
            int reviewNumber = 1;
            // iterasi melalui setiap ulasan dan menampilkan informasi
            while (currentReview != NULL)
            {
                // ekstrak nama pengulas dari ulasan
                size_t foundPos = currentReview->review.find("Reviewed by ");

                if (foundPos != string::npos)
                { // ambil bagian dari ulasan yang dimulai dari posisi setelah "Reviewed by "
                    string reviewerUsername = currentReview->review.substr(foundPos + 13);
                    cout << "Review " << reviewNumber << ": " << currentReview->review << endl;
                }
                else
                {
                    cout << "Review " << reviewNumber << ": "
                         << "Error extracting reviewer's username." << endl;
                }

                currentReview = currentReview->next;
                reviewNumber++;
            }
        }
        else
        {
            cout << "No reviews available." << endl;
        }

        cout << "======================================" << endl;
        currentLocation = currentLocation->next;
    }

    cout << "Press Enter to continue...";
    getch();
}

// algoritma jump search
TouristLocation *jumpSearch(int targetID)
{   // cek apakah linked list kosong
    if (locationHead == NULL)
    {
        return NULL; // return NULL jika tidak ada data
    }

    int n = 0;
    TouristLocation *currentLocation = locationHead;
    // menghitung jumlah elemen dalam linked lis
    while (currentLocation != NULL)
    {
        n++;
        currentLocation = currentLocation->next;
    }

    int step = sqrt(n);
    currentLocation = locationHead;

    // melakukan pencarian melompati blok
    while (currentLocation != NULL && currentLocation->id < targetID)
    {
        currentLocation = currentLocation->next;
        TouristLocation *prevLocation = currentLocation;
        // melompati blok sejauh step
        for (int i = 1; i < step && currentLocation->next != NULL; i++)
        {
            prevLocation = currentLocation;
            
        }
        // jika id lokasi saat ini lebih besar atau sama dengan targetID, keluar dari loop
        if (currentLocation->id >= targetID)
        {
            break;
        }

        // jika masih ada blok berikutnya, pindah ke blok tersebut
        if (currentLocation->next != NULL)
        {
            currentLocation = currentLocation->next;
        }
        else
        {
            break;
        }
    }

    // pencarian linear di dalam blok
    while (currentLocation != NULL && currentLocation->id < targetID)
    {
        currentLocation = currentLocation->next;
    }
    // mengembalikan hasil pencarian (lokasi yang ditemukan atau NULL jika tidak ditemukan)
    if (currentLocation != NULL && currentLocation->id == targetID)
    {
        return currentLocation; // lokasi ditemukan, mengembalikan pointer ke lokasi tersebut
    }
    else
    {
        return NULL; // lokasi tidak ditemukan, mengembalikan NULL
    }
}
// fungsi pencarian untuk mencari lokasi
void searching()
{
    cin.ignore(); // Membersihkan buffer
    int targetID;
    cout << "Enter the ID of the location to search: ";
    cin >> targetID;
    // melakukan pencarian menggunakan algoritma jump search
    TouristLocation *result = jumpSearch(targetID);
    // menampilkan hasil pencarian
    if (result != NULL)
    {
        cout << "Location found:" << endl;
        cout << "Location Name: " << result->name << endl;
        cout << "Description: " << result->description << endl;
        cout << "Rating: " << result->rating << " / 5.0" << endl;
    }
    else
    {
        cout << "Location not found." << endl;
    }

    cout << "Press Enter to continue...";
    cin.ignore(); // membersihkan buffer sebelum melanjutkan
    getch();
}

// fungsi untuk menambahkan review ke dalam struktur tumpukan (stack)
void pushReview(Review *&stackTop, const string &reviewText)
{   // membuat review baru
    Review *newReview = new Review;
    newReview->review = reviewText;
    newReview->next = stackTop;
    stackTop = newReview; // menjadikan review baru sebagai elemen teratas (top) dari tumpukan
}
// fungsi untuk menghapus review dari struktur tumpukan (stack)
void popReview(Review *&stackTop)
{   // memastikan bahwa tumpukan tidak kosong sebelum menghapus
    if (stackTop != NULL)
    {   // menghapus elemen teratas (top) dari tumpukan
        Review *temp = stackTop;
        stackTop = stackTop->next;
        delete temp;
    }
}
// fungsi untuk menambahkan review ke lokasi wisata
void addReview()
{
    // memeriksa apakah data lokasi wisata sudah ada
    if (locationHead == NULL)
    {
        cout << "No Data Found. Cannot add Review." << endl;
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    string locationName;
    cout << "Enter the name of the location to add a review for: ";
    cin.ignore();
    getline(cin, locationName);

    TouristLocation *currentLocation = locationHead;
    // mencari lokasi wisata dengan nama yang sesuai
    while (currentLocation != NULL)
    {
        if (currentLocation->name == locationName)
        {
            cout << "Enter your review: ";
            string reviewText;
            getline(cin, reviewText);

            // menggunakan username pengguna yang sedang masuk
            string reviewerUsername = savedUsername;

            // memeriksa apakah review sudah mengandung "Reviewed by" untuk menghindari duplikasi
            if (reviewText.find("Reviewed by " + reviewerUsername) == string::npos)
            {
                reviewText += "\tReviewed by " + reviewerUsername;
            }

            // menambahkan review ke dalam tumpukan pada lokasi wisata
            pushReview(currentLocation->reviews, reviewText);

            cout << "Review added successfully!" << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            return;
        }

        currentLocation = currentLocation->next;
    }

    cout << "Location not found." << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

int main()
{
    while (true)
    {
        string choiceStr;
        system("cls"); // membersihkan layar konsol
        // menampilkan menu utama
        cout << "===================================================" << endl;
        cout << "|  Welcome to Tourist Location Management System  |" << endl;
        cout << "===================================================" << endl;
        cout << "| Login Options:                                  |" << endl;
        cout << "| 1) Admin                                        |" << endl;
        cout << "| 2) User                                         |" << endl;
        cout << "| 3) Exit Program                                 |" << endl;
        cout << "===================================================" << endl;
        cout << "Enter choice (1-3): ";
        cin >> choiceStr; // menerima pilihan dari pengguna

        try
        {
            int choice = stoi(choiceStr);
            // memproses pilihan pengguna
            switch (choice)
            {
            case 1:
                adminLogin();
                break;
            case 2:
                displayUserMenu();
                break;
            case 3:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                cout << "Press Enter to continue...";
                getch();
                break;
            }
        }
        catch (const invalid_argument &e)
        {
             // menangani kesalahan jika input bukan angka
            cout << "Invalid input. Please enter a valid option (1-3)." << endl;
            cout << "Press Enter to continue...";
            getch();
        }
    }
}
