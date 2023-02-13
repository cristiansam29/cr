#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <fstream>
using namespace std;



const int ENVIRONMENT_SIZE = 256;
const int PATH_STRING_LEN = 5;
const int COMSPEC_LEN = 12;

std::string PATH_STRING = "PATH=";
std::string USER_PATH = "";
std::string COMSPEC = "/COMMAND.COM";
const std::string RESGROUP_RBADNAM = "RESGROUP:RBADNAM";
const std::string RESGROUP_TOOBIG = "RESGROUP:TOOBIG";
const std::string RESGROUP_EXEBAD = "RESGROUP:EXEBAD";
const std::string RESGROUP_EXECEMES = "RESGROUP:EXECEMES";

const int CHAR_OPER = 0x4F;
const int SET_VERIFY_ON_WRITE = 0x43;
const int int_command = 0x21;
constexpr int ENVIRONSIZ = 134;

struct EnvVars
{
    std::string pathstring = "PATH=";
    std::string userpath = "";
    std::string comspec = "COMSPEC=/COMMAND.COM";
};


struct RESGROUP {
  char RSTACK[16];
  int VERVAL;
  int SINGLECOM;
  int SUM;
  int RSWITCHAR;
  int RDIRCHAR;
  char TRANVARS[16];
};

struct TRANGROUP {
  int HEADCALL;
  int MEMSIZ;
  int PDB_block_len;
  int TRANS;
};

extern "C" void HEADFIX();
extern "C" void SETVECT();
extern "C" void CHKSUM();
extern "C" void LOADCOM();
extern "C" void WRONGCOM();
extern "C" void REMCHECK();

bool IBMVER = false;
int EXESUM;
int LOADING = 0;
const uint16_t IO_SAVE = 0;
const uint16_t PDB_JFN_Table = 0;
const uint16_t FilPerProc = 0;
const uint16_t HANDLE01 = 0;
const uint16_t GET_CURRENT_PDB = 0;
const uint16_t CLOSE = 0;
const uint16_t GET_DEFAULT_DRIVE = 0;
const uint16_t int_command = 0;
const uint8_t IBM = 0;
const uint8_t COMDRV = 0;
const char NOCOM[] = "";
const char NEEDCOM[] = "";
const char DRVMSG[] = "";
const char DEFMSG[] = "";
const char PROMPT[] = "";

bool remcheck(uint8_t drive)
{
if (IBM)
{
uint8_t max_floppy = 0;
uint8_t bl = drive;
if (drive == 0)
{
drive = GET_DEFAULT_DRIVE;
int_command(0x11, drive);
drive = 1;
}
drive = ((drive << 1) << 1) & 3;
if (drive == 0)
drive++;
max_floppy = drive;
if (bl <= max_floppy)
return false;
if (drive == 0)
return true;
}
else
{
return false;
}
return true;
}

void headfix()
{
uint16_t bx = 0;
uint16_t cx = IO_SAVE;
uint16_t dx = PDB_JFN_Table;
if (cx == dx)
{
// Stdin matches
}
else
{
int_command(CLOSE, 0);
PDB_JFN_Table = cx; // Restore stdin
}
bx++;
dx = PDB_JFN_Table + 1;
if (cx == dx)
{
// Stdout matches
}
else
{
int_command(CLOSE, 0);
PDB_JFN_Table = cx; // Restore stdout
}
bx += 4; // Skip 2,3,4
cx = FilPerProc - 5; // Already done 0,1,2,3,4
for (uint16_t i = 0; i < cx; i++, bx++)
int_command(CLOSE, 0);
}

void saventhand()
{
uint16_t ax = 0;
uint16_t bx = 0;
uint16_t ds = 0;
ds = GET_CURRENT_PDB;
int_command(GET_CURRENT_PDB, ds);
ds = bx;
ax = PDB_JFN_Table;
HANDLE01 = ax; // Save user's std
//detenido


const int int_command = 0x21;
const int GET_DEFAULT_DRIVE = 0x0e;
const int CLOSE = 0x3e;
const int GET_CURRENT_PDB = 0x62;
const int FilPerProc = 5;

int HANDLE01;
int IO_SAVE;
int PDB_JFN_Table;
int COMDRV;

// Returns zero if media removable, non-zero if fixed
int REMCHECK(int AL) {
    int AX, BX;
    if (AL == 0) {
        AX = GET_DEFAULT_DRIVE;
        // int 21h
        AL++;
    }
    BX = AL;
    // int 11h
    AL = ((AL << 1) << 1) & 3;
    if (AL == 0) {
        AL++;
    }
    if (BX <= AL) {
        return 0;
    }
    return AL | AL;
}

void HEADFIX() {
    int BX, CX, DX;
    BX = 0;
    CX = IO_SAVE;
    DX = PDB_JFN_Table;
    if (CX == DL) {
        // goto CHK1;
    } else {
        int AH = CLOSE;
        // int 21h
        PDB_JFN_Table = CX;
    }
    BX++;
    if (CX == DH) {
        // goto CHKOTHERHAND;
    } else {
        int AH = CLOSE;
        // int 21h
        PDB_JFN_Table = (PDB_JFN_Table & 0xff00) + CH;
    }
    BX += 4;
    int CL = FilPerProc - 5;
    for (int i = 0; i < CL; i++) {
        int AH = CLOSE;
        // int 21h
        BX++;
    }
}

void SAVHAND() {
    int AX, BX, DS;
    __asm {
        push DS
        push BX
        push AX
        mov AH, GET_CURRENT_PDB
        // int 21h
        mov DS, BX
        mov AX, PDB_JFN_Table
        mov HANDLE01, AX
        mov AL, PDB_JFN_Table + 2
        mov AH, AL
        mov PDB_JFN_Table, AX
        pop AX
        pop BX
        pop DS
    }
}

void RESTHAND() {
    int AX, BX, DS;
    __asm {
        push DS
        push BX
        push AX
        mov AH, GET_CURRENT_PDB
        // int 21h
        mov AX, HANDLE01
        mov DS, BX
        mov PDB_JFN_Table, AX
        pop AX
        pop BX
        pop DS
    }
}

void GETCOMDSK() {
    int DX;
    int AL = COMDRV;
//detenido//

void GetRawFlushedByte() {
cin.clear();
cin.sync();
cin >> noskipws;
char ch;
cin >> ch;
cin >> skipws;
}

void LoadCom() {
static bool loaded = false;
if (!loaded) {
string line;
ifstream file("COMMAND.COM");
if (file.is_open()) {
while (getline(file, line)) {
// do something with the line//
}
file.close();
} else {
cout << "Error: unable to open COMMAND.COM" << endl;
GetRawFlushedByte();
}
loaded = true;
}
}


int main()
{
	EnvVars env;
	char environment[ENVIRONMENT_SIZE];
	int environment_len = PATH_STRING_LEN + USER_PATH.length() + 1 + COMSPEC_LEN + 1;

    std::cout << env.pathstring << env.userpath << std::endl;
    std::cout << env.comspec << std::endl;


// Copy PATH_STRING to environment
for (int i = 0; i < PATH_STRING_LEN; i++) {
environment[i] = PATH_STRING[i];
}

// Copy USER_PATH to environment
int j = 0;
for (int i = PATH_STRING_LEN; i < PATH_STRING_LEN + USER_PATH.length(); i++) {
environment[i] = USER_PATH[j++];
}

// Add null terminator for USER_PATH
environment[PATH_STRING_LEN + USER_PATH.length()] = '\0';

// Copy COMSPEC to environment
j = 0;
for (int i = PATH_STRING_LEN + USER_PATH.length() + 1; i < PATH_STRING_LEN + USER_PATH.length() + 1 + COMSPEC_LEN; i++) {
environment[i] = COMSPEC[j++];
}

// Add null terminator for COMSPEC
environment[PATH_STRING_LEN + USER_PATH.length() + 1 + COMSPEC_LEN] = '\0';

// Pad environment with null terminators
for (int i = PATH_STRING_LEN + USER_PATH.length() + 1 + COMSPEC_LEN + 1; i < ENVIRONMENT_SIZE; i++) {
environment[i] = '\0';
}

// Abre el archivo "executable.exe"
ifstream file("executable.exe", ios::binary | ios::in);
if (!file.is_open()) {
cout << "No se pudo abrir el archivo" << endl;
return 1;
}

// Obtiene el tamaño del archivo
file.seekg(0, ios::end);
int size = file.tellg();
file.seekg(0, ios::beg);

// Reservar memoria para el archivo
char* buffer = new char[size];
if (buffer == nullptr) {
cout << "No se pudo reservar suficiente memoria" << endl;
return 1;
}

// Leer el contenido del archivo a la memoria
file.read(buffer, size);
if (!file.good()) {
cout << "Error al leer el archivo" << endl;
return 1;
}

// Cerrar el archivo
file.close();

// Verificar la suma de comprobación del archivo
int checksum = 0;
for (int i = 0; i < size; ++i) {
checksum += buffer[i];
}

if (checksum != 12345) {
cout << "La suma de comprobación no coincide" << endl;
return 1;
}

// Ejecutar el archivo en memoria
cout << "Ejecutando el archivo" << endl;
// ...

// Liberar la memoria
delete[] buffer;

int exec_file_not_found = 1;
int error_access_denied = 2;
int exec_not_enough_memory = 3;
int exec_bad_format = 4;
int ax;


std::cout << "Introduce el valor de AX: ";
std::cin >> ax;

std::string dx;

if (ax == exec_file_not_found || ax == error_access_denied)
{
    dx = RESGROUP_EXECEMES;
    std::cout << "DX es igual a " << dx << std::endl;
}
else if (ax == exec_not_enough_memory)
{
    dx = RESGROUP_TOOBIG;
    std::cout << "DX es igual a " << dx << std::endl;
}
else if (ax == exec_bad_format)
{
    dx = RESGROUP_EXEBAD;
    std::cout << "DX es igual a " << dx << std::endl;
}
else
{
    dx = RESGROUP_RBADNAM;
    std::cout << "DX es igual a " << dx << std::endl;
}

  // Make sure files closed stdin and stdout restored
  HEADFIX();

  int BP = 0;
  int AX = -1;
  int AH = 0;
  int DL = 0;

  // Flag command ok
  BP = 0;

  // Save value in AX
  AX = -1;

  // Swap values
  std::swap(AX, RESGROUP::VERVAL);

  // Compare values
  if (AX == -1) {
    // Value not changed, no need to set verify on write
  } else {
    // Set verify on write
    AH = SET_VERIFY_ON_WRITE;
    int result = int_command;
  }

  // Check if single command
  if (RESGROUP::SINGLECOM != -1) {
    // No single command
  } else {
    // We have finished the single command
    return 0;
  }

  SETVECT();

  // Check exe loader
  if (IBMVER) {
    int result = EXECHK();
    if (result != EXESUM) {
      // Bogus command
      return 0;
    }
  }

  // Check the transient
  int sum = CHKSUM();
  if (sum == RESGROUP::SUM) {
    // Transient OK
    DL = CHAR_OPER << 8;
    int result = int_command;
    RESGROUP::RSWITCHAR = DL;
    if (DL != '/') {
      RESGROUP::RDIRCHAR = '\\';
    } else {
      RESGROUP::RDIRCHAR = '/';
    }
    LOADING = 0;
    std::memcpy(TRANGROUP::TRANVARS, RESGROUP::TRANVARS, 16);
    TRANGROUP::PDB_block_len = RESGROUP::MEMSIZ;
    int result = TRANGROUP::TRANS;
  } else {
    // Check exe loader again
    if (IBMVER) {
      int result = EXECHK();
      if (result != EXESUM) {
        // Also bogus
        WRONGCOM();}
        
DWORD drives = GetLogicalDrives();

    if (drives == 0)
    {
        std::cout << "No se pudo obtener una lista de unidades de disco lógicas." << std::endl;
        return 1;
    }

    TCHAR buffer[3];
    _stprintf_s(buffer, _T("%c:\\"), 'A');
    for (int i = 0; i < 26; i++)
    {
        if (drives & (1 << i))
        {
            std::cout << buffer << std::endl;
        }
        _stprintf_s(buffer, _T("%c:\\"), 'A' + i + 1);
    } 
    LoadCom();
    
return 0;
}
