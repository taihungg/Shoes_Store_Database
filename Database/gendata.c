#include <stdio.h>  // Thư viện chuẩn cho các hàm nhập/xuất
#include <stdlib.h> // Cho rand() và srand()
#include <time.h>   // Cho time()
#include <string.h> // Cần thiết cho hàm strcpy

char customer_ids[99999][9];
char product_ids[999999][9];
char variant_ids[9999999][9];
char feedback_ids[99999][9];
char order_ids[99999][9];
char orderdetail_ids[99999][9];
char employee_ids[99999][9];

// Ham tao so ngau nhien trong mot khoang
int random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// Ham tao so thuc ngau nhien trong mot khoang
double random_double(double min, double max)
{
    return min + ((double)rand() / RAND_MAX) * (max - min);
}

// Các thuộc tính của bảng khách hàng
const char *first_name[200] = {
    "Thanh Tùng", "Mỹ Tâm", "Quốc Bảo", "Thuỳ Chi", "Đức Phúc", "Hồng Nhung", "Đăng Khôi", "Bích Phương",
    "Thành Trung", "Minh Hằng", "Tuấn Hưng", "Khánh Ly", "Gia Khiêm", "Bảo Thy", "Trọng Hiếu", "Thanh Lam",
    "Hoàng Bách", "Kim Anh", "Nhật Tinh Anh", "Tóc Tiên", "Phan Mạnh Quỳnh", "Đông Nhi", "Chí Thiện", "Hương Tràm",
    "Anh Quân", "Cẩm Ly", "Khắc Việt", "Uyên Linh", "Cao Thái Sơn", "Hồ Ngọc Hà", "Quang Vinh", "Phương Thanh",
    "Đại Nhân", "Lệ Quyên", "Ưng Hoàng Phúc", "Mỹ Lệ", "Bằng Kiều", "Hari Won", "Lam Trường", "Thủy Tiên",
    "Đan Trường", "Vy Oanh", "Lý Hải", "Hiền Thục", "Phạm Trưởng", "Thu Minh", "Châu Khải Phong", "Văn Mai Hương",
    "Akira Phan", "Bảo Anh",
    "James", "Mary", "Robert", "Patricia", "John", "Jennifer", "Michael", "Linda", "David", "Elizabeth",
    "William", "Barbara", "Richard", "Susan", "Joseph", "Jessica", "Thomas", "Sarah", "Charles", "Karen",
    "Daniel", "Lisa", "Matthew", "Nancy", "Anthony", "Betty", "Mark", "Margaret", "Donald", "Sandra",
    "Steven", "Ashley", "Paul", "Kimberly", "Andrew", "Emily", "Joshua", "Donna", "Kevin", "Michelle",
    "Brian", "Carol", "George", "Amanda", "Timothy", "Melissa", "Ronald", "Deborah", "Jason", "Stephanie",
    "Christopher", "Jessica", "Brian", "Angela", "Kevin", "Melissa", "Edward", "Brenda", "Ronald", "Nicole",
    "Timothy", "Heather", "Jason", "Amber", "Jeffrey", "Crystal", "Ryan", "Megan", "Jacob", "Brittany",
    "Gary", "Christina", "Nicholas", "Rachel", "Eric", "Laura", "Stephen", "Danielle", "Jonathan", "Tiffany",
    "Larry", "Michelle", "Justin", "Wendy", "Scott", "Sara", "Brandon", "Erica", "Benjamin", "Amy",
    "Samuel", "Rebecca", "Gregory", "April", "Frank", "Mary", "Alexander", "Shannon", "Patrick", "Tina",
    "Walter", "Tracy", "Peter", "Erin", "Henry", "Julie", "Jerry", "Maria", "Douglas", "Denise",
    "Dennis", "Andrea", "Arthur", "Jamie", "Roger", "Kelly", "Terry", "Stacy", "Lawrence", "Holly",
    "Sean", "Dawn", "Christian", "Kathleen", "Ethan", "Brandy", "Austin", "Monica", "Joe", "Annette",
    "Albert", "Tonya", "Jesse", "Catherine", "Willie", "Teresa", "Carl", "Jodi", "Billy", "Kara",
    "Bruce", "Cynthia", "Ralph", "Gina", "Bryan", "Jacqueline", "Roy", "Heidi", "Jordan", "Victoria"};

const char *last_name[200] = {
    "Nguyễn", "Trần", "Lê", "Phạm", "Hoàng", "Vũ", "Phan", "Trương", "Bùi", "Đặng", "Đỗ", "Ngô", "Hồ", "Dương",
    "Lý", "Đoàn", "Vương", "Trịnh", "Đinh", "Lâm", "Phùng", "Mai", "Tô", "Hà", "Tạ", "Lưu", "Châu", "Mạc",
    "Thái", "Tạ", "Huỳnh", "Tôn", "Uông", "Cung", "Giang", "Đàm", "Từ", "Tào", "Kiều", "Ông", "Vi", "Thạch",
    "Nhâm", "Lại", "Tiêu", "Doãn", "Nhan", "La", "Quan", "Tiền",
    "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez",
    "Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin",
    "Lee", "Perez", "Thompson", "White", "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson",
    "Walker", "Young", "Allen", "King", "Wright", "Scott", "Torres", "Nguyen", "Hill", "Flores",
    "Green", "Adams", "Nelson", "Baker", "Hall", "Rivera", "Campbell", "Mitchell", "Carter", "Roberts",
    "Parker", "Evans", "Edwards", "Collins", "Stewart", "Morris", "Murphy", "Cook", "Rogers", "Morgan",
    "Peterson", "Cooper", "Reed", "Bailey", "Bell", "Gomez", "Kelly", "Howard", "Ward", "Cox",
    "Diaz", "Richardson", "Wood", "Watson", "Brooks", "Bennett", "Gray", "James", "Reyes", "Cruz",
    "Hughes", "Price", "Myers", "Long", "Foster", "Sanders", "Ross", "Morales", "Powell", "Sullivan",
    "Russell", "Ortiz", "Jenkins", "Gutierrez", "Perry", "Butler", "Barnes", "Fisher", "Henderson", "Coleman",
    "Patterson", "Jordan", "Graham", "Reynolds", "Hamilton", "Ford", "Gibson", "Wallace", "Simpson", "West",
    "Spencer", "Pierce", "Porter", "Mason", "Gordon", "Shaw", "Holmes", "Rice", "Hunt", "Black",
    "Daniels", "Palmer", "Robertson", "Harrison", "Duncan", "Hart", "Stone", "Warren", "Hawkins", "Webb",
    "Elliott", "Chavez", "Snyder", "Hunter", "Hicks", "Crawford", "Henry", "Boyd", "Mason", "Kennedy",
    "Lawson", "Garza", "Franklin", "Payne", "Armstrong", "Burke", "Stevens", "Marshall", "Soto", "Matthews"};

const char *city[200] = {
    "Hà Nội", "TP. Hồ Chí Minh", "Đà Nẵng", "Hải Phòng", "Cần Thơ", "Nha Trang", "Bình Dương", "Đồng Nai",
    "Vũng Tàu", "Thừa Thiên Huế", "Quảng Ninh", "Lâm Đồng", "Kiên Giang", "Thanh Hóa", "Nghệ An", "Bắc Ninh",
    "Hà Nội", "TP. Hồ Chí Minh", "Đà Nẵng", "Hải Phòng", "Cần Thơ", "Nha Trang", "Bình Dương", "Đồng Nai",
    "Vũng Tàu", "Thừa Thiên Huế", "Quảng Ninh", "Lâm Đồng", "Kiên Giang", "Thanh Hóa", "Nghệ An", "Bắc Ninh",
    "Hà Nội", "TP. Hồ Chí Minh", "Đà Nẵng", "Hải Phòng", "Cần Thơ", "Nha Trang", "Bình Dương", "Đồng Nai",
    "Vũng Tàu", "Thừa Thiên Huế", "Quảng Ninh", "Lâm Đồng", "Kiên Giang", "Thanh Hóa", "Nghệ An", "Bắc Ninh",
    "Hà Nội", "TP. Hồ Chí Minh",
    "New York", "London", "Tokyo", "Paris", "Sydney", "Berlin", "Toronto", "Singapore", "Dubai", "Los Angeles",
    "Chicago", "Rome", "Madrid", "Moscow", "Beijing", "Mumbai", "Cairo", "Rio de Janeiro", "Mexico City", "Seoul",
    "Amsterdam", "Dublin", "Stockholm", "Vienna", "Lisbon", "Prague", "Warsaw", "Budapest", "Athens", "Helsinki",
    "Oslo", "Copenhagen", "Brussels", "Zurich", "Geneva", "Vancouver", "Melbourne", "Auckland", "Bangkok", "Kuala Lumpur",
    "Hong Kong", "Taipei", "Manila", "Jakarta", "New Delhi", "Istanbul", "Tel Aviv", "Sao Paulo", "Buenos Aires", "Santiago",
    "Barcelona", "Milan", "Munich", "Vienna", "Zurich", "Brussels", "Copenhagen", "Stockholm", "Helsinki", "Oslo",
    "Warsaw", "Prague", "Budapest", "Athens", "Istanbul", "Lisbon", "Edinburgh", "Manchester", "Liverpool", "Glasgow",
    "Montreal", "Vancouver", "Calgary", "Ottawa", "Quebec City", "Auckland", "Wellington", "Christchurch", "Perth", "Brisbane",
    "Adelaide", "Canberra", "Kyoto", "Osaka", "Sapporo", "Fukuoka", "Incheon", "Busan", "Kuala Lumpur", "Penang",
    "Bangkok", "Chiang Mai", "Phuket", "Hanoi", "Ho Chi Minh City", "Jakarta", "Bali", "Manila", "Cebu", "Davao",
    "New Delhi", "Bangalore", "Chennai", "Kolkata", "Hyderabad", "Mumbai", "Pune", "Jaipur", "Agra", "Goa",
    "Cairo", "Alexandria", "Giza", "Luxor", "Aswan", "Marrakech", "Casablanca", "Fes", "Rabat", "Tangier",
    "Cape Town", "Johannesburg", "Durban", "Pretoria", "Port Elizabeth", "Nairobi", "Mombasa", "Lagos", "Abuja", "Accra",
    "Mexico City", "Cancun", "Guadalajara", "Tijuana", "Monterrey", "Rio de Janeiro", "Sao Paulo", "Salvador", "Brasilia", "Fortaleza",
    "Buenos Aires", "Mendoza", "Cordoba", "Rosario", "Santiago", "Valparaiso", "Lima", "Cusco", "Bogota", "Medellin"};

const char *district[200] = {
    "Ba Đình", "Quận 1", "Hải Châu", "Ngô Quyền", "Ninh Kiều", "Lộc Thọ", "Dĩ An", "Biên Hòa",
    "Phường 7", "TP. Huế", "Hạ Long", "Đà Lạt", "Phú Quốc", "Sầm Sơn", "TP. Vinh", "Từ Sơn",
    "Cầu Giấy", "Quận 3", "Thanh Khê", "Lê Chân", "Cái Răng", "Vĩnh Hải", "Thuận An", "Long Khánh",
    "Phường 1", "Hương Thủy", "Cẩm Phả", "Bảo Lộc", "Rạch Giá", "TP. Thanh Hóa", "Cửa Lò", "Yên Phong",
    "Đống Đa", "Quận 5", "Sơn Trà", "Hồng Bàng", "Bình Thủy", "Vĩnh Nguyên", "Tân Uyên", "Xuân Lộc",
    "Phường 2", "Phú Lộc", "Uông Bí", "Di Linh", "Hà Tiên", "Bỉm Sơn", "Hoàng Mai", "Quế Võ",
    "Hoàn Kiếm", "Quận 7",
    "Manhattan", "Westminster", "Shibuya", "Le Marais", "The Rocks", "Mitte", "Downtown", "Marina Bay", "Downtown Dubai", "Hollywood",
    "The Loop", "Trastevere", "Centro", "Tverskoy", "Dongcheng", "Colaba", "Zamalek", "Copacabana", "Polanco", "Gangnam",
    "Jordaan", "Temple Bar", "Gamla Stan", "Innere Stadt", "Alfama", "Old Town", "Śródmieście", "Castle District", "Plaka", "Kallio",
    "Grünerløkka", "Indre By", "Sablon", "District 1", "Eaux-Vives", "Gastown", "Fitzroy", "Parnell", "Sukhumvit", "Bukit Bintang",
    "Central", "Xinyi", "Makati", "Menteng", "Connaught Place", "Beyoğlu", "Neve Tzedek", "Jardins", "Palermo", "Providencia",
    "Gràcia", "Navigli", "Schwabing", "Neubau", "Old Town", "Ixelles", "Vesterbro", "Södermalm", "Punavuori", "Frogner",
    "Praga-Północ", "Žižkov", "Erzsébetváros", "Psiri", "Karaköy", "Bairro Alto", "Old Town", "Northern Quarter", "Baltic Triangle", "West End",
    "Plateau Mont-Royal", "Kitsilano", "Kensington", "ByWard Market", "Petit Champlain", "Mount Eden", "Te Aro", "Riccarton", "Fremantle", "South Bank",
    "North Adelaide", "Braddon", "Gion", "Dotonbori", "Susukino", "Tenjin", "Songdo", "Haeundae", "Bangsar", "George Town",
    "Thonglor", "Nimmanhaemin", "Patong", "Old Quarter", "District 1", "Kemang", "Seminyak", "Bonifacio Global City", "Lahug", "Poblacion District",
    "Hauz Khas Village", "Koramangala", "T. Nagar", "Park Street", "Banjara Hills", "Bandra West", "Koregaon Park", "C Scheme", "Taj Ganj", "Calangute",
    "Garden City", "Montaza", "Haram", "Karnak", "Nubian Village", "Gueliz", "Anfa", "Fes el Bali", "Hassan", "Kasbah",
    "Camps Bay", "Sandton", "Umhlanga", "Arcadia", "Summerstrand", "Westlands", "Nyali", "Victoria Island", "Asokoro", "Osu",
    "Condesa", "Zona Hotelera", "Chapultepec", "Zona Rio", "San Pedro Garza García", "Ipanema", "Vila Madalena", "Pelourinho", "Asa Sul", "Praia de Iracema",
    "Recoleta", "Plaza Independencia", "Nueva Córdoba", "Fisherton", "Lastarria", "Cerro Alegre", "Miraflores", "San Blas", "La Candelaria", "El Poblado"};

const char *address[200] = {
    "12 Điện Biên Phủ", "21 Nguyễn Trãi", "34 Bạch Đằng", "56 Lạch Tray", "78 Hòa Bình", "90 Trần Phú",
    "11 Lý Thường Kiệt", "22 Đồng Khởi", "33 Thùy Vân", "44 Lê Lợi", "55 Trần Hưng Đạo", "66 Phan Đình Phùng",
    "77 Mạc Cửu", "88 Lê Hoàn", "99 Quang Trung", "10 Nguyễn Gia Thiều", "123 Xuân Thủy", "234 Nam Kỳ Khởi Nghĩa",
    "345 Nguyễn Văn Linh", "456 Cầu Đất", "567 Cách Mạng Tháng 8", "678 Phạm Văn Đồng", "789 Quốc lộ 13", "890 Quốc lộ 1A",
    "901 Lê Hồng Phong", "12 Hùng Vương", "23 Hoàng Quốc Việt", "34 Hồ Tùng Mậu", "45 Nguyễn Lương Bằng", "56 Bà Triệu",
    "67 Hai Bà Trưng", "78 Lý Tự Trọng", "89 Hoàng Diệu", "90 Pasteur", "135 Lê Thánh Tôn", "246 Hai Bà Trưng",
    "357 Trần Quang Khải", "468 Võ Thị Sáu", "579 Tôn Đức Thắng", "680 Nguyễn Hữu Cảnh", "791 Nguyễn Kiệm", "802 Phan Xích Long",
    "913 Lê Văn Sỹ", "147 Nguyễn Thái Học", "258 Hoàng Hoa Thám", "369 Cách Mạng Tháng 8", "470 Âu Cơ", "581 Lạc Long Quân",
    "692 An Dương Vương", "703 Nguyễn Oanh",
    "123 Broadway", "456 Oxford Street", "789 Hachiko Square", "101 Rue de Rivoli", "12 Circular Quay", "13 Unter den Linden", "14 Bay Street", "15 Raffles Avenue",
    "16 Sheikh Mohammed bin Rashid Blvd", "17 Hollywood Boulevard", "18 North Michigan Avenue", "19 Via della Lungara", "20 Gran Vía", "21 Tverskaya Street",
    "22 Wangfujing Street", "23 Marine Drive", "24 Sharia Tahrir", "25 Avenida Atlântica", "26 Av. Presidente Masaryk", "27 Gangnam-daero",
    "28 Prinsengracht", "29 Dame Street", "30 Västerlånggatan", "31 Kärntner Strasse", "32 Rua da Saudade", "33 Staroměstské náměstí",
    "34 Nowy Świat", "35 Szent György tér", "36 Adrianou Street", "37 Helsinginkatu", "38 Thorvald Meyers gate", "39 Strøget", "40 Rue Haute",
    "41 Bahnhofstrasse", "42 Rue du Rhône", "43 Water Street", "44 Brunswick Street", "45 Parnell Road", "46 Sukhumvit Road", "47 Jalan Bukit Bintang",
    "48 Queens Road Central", "49 Songgao Road", "50 Ayala Avenue", "51 Jalan HOS. Cokroaminoto", "52 Janpath", "53 İstiklal Avenue",
    "54 Shabazi Street", "55 Rua Oscar Freire", "56 Av. del Libertador", "57 Av. Nueva Providencia",
    "101 Carrer de Verdi", "102 Ripa di Porta Ticinese", "103 Hohenzollernstraße", "104 Mariahilfer Straße", "105 Niederdorfstrasse", "106 Chaussée dIxelles", "107 Istedgade", "108 Götgatan", "109 Uudenmaankatu", "110 Bygdøy allé",
    "111 Ząbkowska", "112 Koněvova", "113 Király utca", "114 Karaiskaki", "115 Kemankeş Karamustafa Paşa", "116 Rua da Atalaia", "117 Royal Mile", "118 Oldham Street", "119 Jamaica Street", "120 Ashton Lane",
    "121 Avenue du Mont-Royal", "122 West 4th Avenue", "123 10th Street NW", "124 George Street", "125 Rue du Petit Champlain", "126 Mount Eden Road", "127 Cuba Street", "128 Riccarton Road", "129 South Terrace", "130 Grey Street",
    "131 OConnell Street", "132 Lonsdale Street", "133 Hanamikoji Dori", "134 Shinsaibashi-suji", "135 Tanukikoji Shopping Street", "136 Tenjin Nishi-dori", "137 Convensia-daero", "138 Haeundaehaebyeon-ro", "139 Jalan Telawi", "140 Lebuh Chulia",
    "141 Sukhumvit Soi 55", "142 Nimmanahaeminda Road", "143 Thawewong Road", "144 Hang Bac Street", "145 Nguyen Hue Walking Street", "146 Jalan Kemang Raya", "147 Jalan Kayu Aya", "148 5th Avenue", "149 Salinas Drive", "150 Don Julio Llorente Street",
    "151 Shivalik", "152 5th Cross Road", "153 Pondy Bazaar", "154 Mother Teresa Sarani", "155 Road No. 1", "156 Linking Road", "157 North Main Road", "158 MI Road", "159 Fatehabad Road", "160 Baga Road",
    "161 Corniche El Nil", "162 El-Gaish Road", "163 Al-Haram Street", "164 Maabad al-Karnak", "165 Gharb Seheil", "166 Avenue Mohammed V", "167 Boulevard de la Corniche", "168 Talaa Kebira", "169 Avenue Chellah", "170 Rue de la Kasbah",
    "171 Victoria Road", "172 5th Street", "173 Lighthouse Road", "174 Stanza Bopape Street", "175 Marine Drive", "176 Waiyaki Way", "177 Links Road", "178 Adeola Odeku Street", "179 Yakubu Gowon Crescent", "180 Oxford Street",
    "181 Av. Amsterdam", "182 Blvd. Kukulcan", "183 Av. Chapultepec", "184 Paseo de los Héroes", "185 Av. José Vasconcelos", "186 Rua Vinicius de Moraes", "187 Rua Aspicuelta", "188 Largo do Pelourinho", "189 CLS 105", "190 Av. Beira Mar",
    "191 Avenida Alvear", "192 Arístides Villanueva", "193 Hipólito Yrigoyen", "194 Bv. Argentino", "195 José Victorino Lastarria", "196 Paseo Dimalow", "197 Av. José Larco", "198 Cuesta de San Blas", "199 Carrera 3", "200 Carrera 43A"};

const char *credit_card[200] = {
    "4552 0000 1123 5813", "5424 0001 2134 8914", "4929 0002 3455 1442", "6011 0003 5589 2334", "4111 0004 8914 3770",
    "5252 0005 1442 5122", "4222 0006 2334 8914", "5123 0007 3770 9872", "4552 0008 5122 3691", "5424 0009 8914 4181",
    "4929 0010 9872 7873", "6011 0011 3691 1094", "4111 0012 4181 8967", "5252 0013 7873 2188", "4222 0014 1094 3282",
    "5123 0015 8967 4376", "4552 0016 2188 5470", "5424 0017 3282 6564", "4929 0018 4376 7658", "6011 0019 5470 8752",
    "4111 0020 6564 9846", "5252 0021 7658 1030", "4222 0022 8752 2124", "5123 0023 9846 3218", "4552 0024 1030 4312",
    "5424 0025 2124 5406", "4929 0026 3218 6500", "6011 0027 4312 7594", "4111 0028 5406 8688", "5252 0029 6500 9782",
    "4222 0030 7594 1076", "5123 0031 8688 2170", "4552 0032 9782 3264", "5424 0033 1076 4358", "4929 0034 2170 5452",
    "6011 0035 3264 6546", "4111 0036 4358 7640", "5252 0037 5452 8734", "4222 0038 6546 9828", "5123 0039 7640 1012",
    "4552 0040 8734 2106", "5424 0041 9828 3200", "4929 0042 1012 4294", "6011 0043 2106 5388", "4111 0044 3200 6482",
    "5252 0045 4294 7576", "4222 0046 5388 8670", "5123 0047 6482 9764", "4552 0048 7576 1058", "5424 0049 8670 2152",
    "4929 0050 9764 3246", "6011 0051 1058 4340", "4111 0052 2152 5434", "5252 0053 3246 6528", "4222 0054 4340 7622",
    "5123 0055 5434 8716", "4552 0056 6528 9810", "5424 0057 7622 1004", "4929 0058 8716 2098", "6011 0059 9810 3192",
    "4111 0060 1004 4286", "5252 0061 2098 5380", "4222 0062 3192 6474", "5123 0063 4286 7568", "4552 0064 5380 8662",
    "5424 0065 6474 9756", "4929 0066 7568 1050", "6011 0067 8662 2144", "4111 0068 9756 3238", "5252 0069 1050 4332",
    "4222 0070 2144 5426", "5123 0071 3238 6520", "4552 0072 4332 7614", "5424 0073 5426 8708", "4929 0074 6520 9802",
    "6011 0075 7614 1096", "4111 0076 8708 2190", "5252 0077 9802 3284", "4222 0078 1096 4378", "5123 0079 2190 5472",
    "4552 0080 3284 6566", "5424 0081 4378 7660", "4929 0082 5472 8754", "6011 0083 6566 9848", "4111 0084 7660 1032",
    "5252 0085 8754 2126", "4222 0086 9848 3220", "5123 0087 1032 4314", "4552 0088 2126 5408", "5424 0089 3220 6502",
    "4929 0090 4314 7596", "6011 0091 5408 8690", "4111 0092 6502 9784", "5252 0093 7596 1078", "4222 0094 8690 2172",
    "5123 0095 9784 3266", "4552 0096 1078 4360", "5424 0097 2172 5454", "4929 0098 3266 6548", "6011 0099 4360 7642",
    "4111 0100 5454 8736", "5252 0101 6548 9830", "4222 0102 7642 1024", "5123 0103 8736 2118", "4552 0104 9830 3212",
    "5424 0105 1024 4306", "4929 0106 2118 5400", "6011 0107 3212 6494", "4111 0108 4306 7588", "5252 0109 5400 8682",
    "4222 0110 6494 9776", "5123 0111 7588 1070", "4552 0112 8682 2164", "5424 0113 9776 3258", "4929 0114 1070 4352",
    "6011 0115 2164 5446", "4111 0116 3258 6540", "5252 0117 4352 7634", "4222 0118 5446 8728", "5123 0119 6540 9822",
    "4552 0120 7634 1016", "5424 0121 8728 2110", "4929 0122 9822 3204", "6011 0123 1016 4298", "4111 0124 2110 5392",
    "5252 0125 3204 6486", "4222 0126 4298 7580", "5123 0127 5392 8674", "4552 0128 6486 9768", "5424 0129 7580 1062",
    "4929 0130 8674 2156", "6011 0131 9768 3250", "4111 0132 1062 4344", "5252 0133 2156 5438", "4222 0134 3250 6532",
    "5123 0135 4344 7626", "4552 0136 5438 8720", "5424 0137 6532 9814", "4929 0138 7626 1008", "6011 0139 8720 2102",
    "4111 0140 9814 3196", "5252 0141 1008 4290", "4222 0142 2102 5384", "5123 0143 3196 6478", "4552 0144 4290 7572",
    "5424 0145 5384 8666", "4929 0146 6478 9760", "6011 0147 7572 1054", "4111 0148 8666 2148", "5252 0149 9760 3242",
    "4222 0150 1054 4336", "5123 0151 2148 5430", "4552 0152 3242 6524", "5424 0153 4336 7618", "4929 0154 5430 8712",
    "6011 0155 6524 9806", "4111 0156 7618 1000", "5252 0157 8712 2094", "4222 0158 9806 3188", "5123 0159 1000 4282",
    "4552 0160 2094 5376", "5424 0161 3188 6470", "4929 0162 4282 7564", "6011 0163 5376 8658", "4111 0164 6470 9752",
    "5252 0165 7564 1046", "4222 0166 8658 2140", "5123 0167 9752 3234", "4552 0168 1046 4328", "5424 0169 2140 5422",
    "4929 0170 3234 6516", "6011 0171 4328 7610", "4111 0172 5422 8704", "5252 0173 6516 9798", "4222 0174 7610 1092",
    "5123 0175 8704 2186", "4552 0176 9798 3280", "5424 0177 1092 4374", "4929 0178 2186 5468", "6011 0179 3280 6562",
    "4111 0180 4374 7656", "5252 0181 5468 8750", "4222 0182 6562 9844", "5123 0183 7656 1028", "4552 0184 8750 2122",
    "5424 0185 9844 3216", "4929 0186 1028 4310", "6011 0187 2122 5404", "4111 0188 3216 6498", "5252 0189 4310 7592",
    "4222 0190 5404 8686", "5123 0191 6498 9780", "4552 0192 7592 1074", "5424 0193 8686 2168", "4929 0194 9780 3262",
    "6011 0195 1074 4356", "4111 0196 2168 5450", "5252 0197 3262 6544", "4222 0198 4356 7638", "5123 0199 5450 8732"};

const char *dob[200] = {
    "1990-01-15", "1981-05-20", "1995-02-10", "1988-11-30", "1995-07-25", "1971-04-12", "1982-01-05", "1989-09-18",
    "1993-06-22", "1984-03-08", "1978-08-20", "1944-02-10", "2005-11-30", "1988-07-25", "1992-04-12", "1970-01-05",
    "1978-09-18", "1980-06-22", "1979-03-08", "1989-05-15", "1985-08-20", "1988-02-10", "1986-11-30", "1993-07-25",
    "1975-04-12", "1976-01-05", "1983-09-18", "1989-06-22", "1984-03-08", "1981-05-15", "1981-08-20", "1975-02-10",
    "1986-11-30", "1981-07-25", "1981-04-12", "1972-01-05", "1975-09-18", "1985-06-22", "1971-03-08", "1985-05-15",
    "1977-08-20", "1986-02-10", "1973-11-30", "1982-07-25", "1979-04-12", "1978-01-05", "1983-09-18", "1994-06-22",
    "1984-03-08", "1991-05-15",
    "1985-06-15", "1992-03-22", "1988-11-01", "1995-09-14", "1980-02-28", "1998-07-19", "1983-04-05", "1991-12-30",
    "1979-01-11", "2001-10-08", "1986-08-17", "1993-05-24", "1989-12-02", "1996-10-15", "1981-03-29", "1999-08-20",
    "1984-05-06", "1992-01-31", "1980-09-12", "1997-11-09", "1987-07-18", "1994-04-25", "1990-12-03", "1998-10-16",
    "1982-04-01", "2000-09-21", "1985-06-07", "1993-02-01", "1981-10-13", "1999-12-10", "1988-08-19", "1995-05-26",
    "1991-01-04", "1999-11-17", "1983-05-02", "2001-10-22", "1986-07-08", "1994-03-02", "1982-11-14", "2000-01-11",
    "1989-09-20", "1996-06-27", "1992-02-05", "2000-12-18", "1984-06-03", "2002-11-23", "1987-08-09", "1995-04-03",
    "1983-12-15", "2001-02-12",
    "1990-01-01", "1991-02-02", "1992-03-03", "1993-04-04", "1994-05-05", "1995-06-06", "1996-07-07", "1997-08-08", "1998-09-09", "1999-10-10",
    "1980-11-11", "1981-12-12", "1982-01-13", "1983-02-14", "1984-03-15", "1985-04-16", "1986-05-17", "1987-06-18", "1988-07-19", "1989-08-20",
    "2000-09-21", "2001-10-22", "2002-11-23", "1990-12-24", "1991-01-25", "1992-02-26", "1993-03-27", "1994-04-28", "1995-05-29", "1996-06-30",
    "1997-07-01", "1998-08-02", "1999-09-03", "1980-10-04", "1981-11-05", "1982-12-06", "1983-01-07", "1984-02-08", "1985-03-09", "1986-04-10",
    "1987-05-11", "1988-06-12", "1989-07-13", "2000-08-14", "2001-09-15", "2002-10-16", "1990-11-17", "1991-12-18", "1992-01-19", "1993-02-20",
    "1994-03-21", "1995-04-22", "1996-05-23", "1997-06-24", "1998-07-25", "1999-08-26", "1980-09-27", "1981-10-28", "1982-11-29", "1983-12-30",
    "1984-01-31", "1985-02-01", "1986-03-02", "1987-04-03", "1988-05-04", "1989-06-05", "2000-07-06", "2001-08-07", "2002-09-08", "1990-10-09",
    "1991-11-10", "1992-12-11", "1993-01-12", "1994-02-13", "1995-03-14", "1996-04-15", "1997-05-16", "1998-06-17", "1999-07-18", "1980-08-19",
    "1981-09-20", "1982-10-21", "1983-11-22", "1984-12-23", "1985-01-24", "1986-02-25", "1987-03-26", "1988-04-27", "1989-05-28", "2000-06-29",
    "2001-07-30", "2002-08-31", "1990-09-01", "1991-10-02", "1992-11-03", "1993-12-04", "1994-01-05", "1995-02-06", "1996-03-07", "1997-04-08"};

const char *gender[2] = {
    "M", "F"};

const char *categories[50][2] = {
    // --- Phân loại theo người dùng ---
    {"MENS", "Giày Nam"},
    {"WMNS", "Giày Nữ"},
    {"UNIS", "Giày Unisex (Cho cả Nam và Nữ)"},
    {"KIDS", "Giày Trẻ Em"},
    {"BOYS", "Giày Bé Trai"},
    {"GIRL", "Giày Bé Gái"},

    // --- Giày thể thao & chuyên dụng ---
    {"RUN", "Giày Chạy Bộ"},
    {"GYM", "Giày Tập Gym & Fitness"},
    {"WALK", "Giày Đi Bộ"},
    {"BASK", "Giày Bóng Rổ"},
    {"FTBL", "Giày Đá Bóng"},
    {"TENN", "Giày Tennis"},
    {"HIKE", "Giày Leo Núi (Hiking)"},
    {"SKTE", "Giày Trượt Ván"},
    {"GOLF", "Giày Chơi Golf"},

    // --- Giày dép thông thường (Casual) ---
    {"SNKR", "Giày Sneaker"},
    {"LIFE", "Giày Thời Trang Hàng Ngày"},
    {"SLIP", "Giày Slip-On (Không dây)"},
    {"LOAF", "Giày Lười"},
    {"CANV", "Giày Vải"},
    {"BOAT", "Giày Lái Thuyền"},
    {"MULE", "Giày Sục (Hở gót)"},

    // --- Giày trang trọng (Formal) ---
    {"DRES", "Giày Tây"},
    {"OXFD", "Giày Oxford"},
    {"DRBY", "Giày Derby"},
    {"MONK", "Giày Monk Strap"},

    // --- Các loại Bốt (Boots) ---
    {"ANKL", "Bốt Cổ Ngắn"},
    {"CHLS", "Bốt Chelsea"},
    {"CHKA", "Bốt Chukka"},
    {"CMBT", "Bốt Chiến Binh"},
    {"WORK", "Bốt Bảo Hộ"},
    {"RAIN", "Ủng Đi Mưa"},

    // --- Giày dép hở ngón & Sandal ---
    {"SAND", "Dép Sandal"},
    {"FLIP", "Dép Kẹp / Dép Xỏ Ngón"},
    {"SLDE", "Dép Quai Ngang"},
    {"CLOG", "Dép Sục / Guốc Gỗ"},
    {"GLAD", "Sandal Chiến Binh"},

    // --- Giày dép đặc thù của nữ ---
    {"HEEL", "Giày Cao Gót"},
    {"PUMP", "Giày Gót Nhọn (Pumps)"},
    {"STIL", "Giày Gót Siêu Nhọn (Stilettos)"},
    {"WDGE", "Giày Đế Xuồng"},
    {"PLAT", "Giày Đế Bánh Mì"},
    {"FLAT", "Giày Búp Bê"},
    {"MARY", "Giày Mary Jane"},

    // --- Giày dép chuyên dụng khác ---
    {"SLPR", "Dép Đi Trong Nhà"},
    {"BECH", "Dép Đi Biển"},
    {"ORTH", "Giày Y Tế (Chỉnh hình)"},

    // --- Phụ kiện giày dép ---
    {"CARE", "Sản Phẩm Chăm Sóc Giày"},
    {"SOLE", "Lót Giày"},
    {"LACE", "Dây Giày"}};

const char *brands[200][2] = {
    // === Nhóm 1: Thương hiệu Thể thao & Dã ngoại (Athletic & Outdoor) === (25)
    {"NIKE", "Nike"},
    {"ADID", "Adidas"},
    {"PUMA", "Puma"},
    {"RBOK", "Reebok"},
    {"NB", "New Balance"},
    {"ASCS", "ASICS"},
    {"UA", "Under Armour"},
    {"SKEC", "Skechers"},
    {"FILA", "Fila"},
    {"MZNO", "Mizuno"},
    {"LNNG", "Li-Ning"},
    {"ANTA", "Anta"},
    {"BRKS", "Brooks Running"},
    {"SAUC", "Saucony"},
    {"HOKA", "Hoka"},
    {"ON", "On Running"},
    {"ALTR", "Altra Running"},
    {"SALO", "Salomon"},
    {"MERL", "Merrell"},
    {"TNF", "The North Face"},
    {"CLMB", "Columbia"},
    {"KEEN", "KEEN"},
    {"LASP", "La Sportiva"},
    {"PATA", "Patagonia Footwear"},
    {"LULU", "Lululemon"},

    // === Nhóm 2: Thời trang Đường phố & Thông dụng (Streetwear & Casual) === (15)
    {"CONS", "Converse"},
    {"VANS", "Vans"},
    {"PLDM", "Palladium"},
    {"SPGA", "Superga"},
    {"KEDS", "Keds"},
    {"TOMS", "TOMS"},
    {"SPRY", "Sperry Top-Sider"},
    {"SBGO", "Sebago"},
    {"DC", "DC Shoes"},
    {"ETNS", "Etnies"},
    {"GLOB", "Globe"},
    {"SPRA", "Supra"},
    {"KSW", "K-Swiss"},
    {"CHMP", "Champion"},
    {"GOLA", "Gola"},

    // === Nhóm 3: Thương hiệu Việt Nam & Quen thuộc tại VN === (10)
    {"BITS", "Bitis"},
    {"ANAS", "Ananas"},
    {"RNVN", "RieNevan"},
    {"VNG", "Vina Giầy"},
    {"JUNO", "Juno"},
    {"VASC", "Vascara"},
    {"MWC", "MWC"},
    {"DOHI", "Giày Đông Hải"},
    {"BITA", "Bitas"},
    {"HOTH", "Giày Hồng Thạnh"},

    // === Nhóm 4: Bốt & Giày Da (Boots & Leather) === (10)
    {"DRM", "Dr. Martens"},
    {"TMBL", "Timberland"},
    {"CLRK", "Clarks"},
    {"RWS", "Red Wing Shoes"},
    {"WOLV", "Wolverine"},
    {"CHIP", "Chippewa Boots"},
    {"UGG", "UGG"},
    {"BLUN", "Blundstone"},
    {"THUR", "Thursday Boot Company"},
    {"FRYE", "Frye Company"},

    // === Nhóm 5: Tiện dụng & Thoải mái (Comfort & Utility) === (15)
    {"CROC", "Crocs"},
    {"BIRK", "Birkenstock"},
    {"ECCO", "ECCO"},
    {"GEOX", "Geox"},
    {"HUSH", "Hush Puppies"},
    {"RCKP", "Rockport"},
    {"NATU", "Naturalizer"},
    {"AERO", "Aerosoles"},
    {"FITF", "FitFlop"},
    {"MEPH", "Mephisto"},
    {"DANS", "Dansko"},
    {"SNUK", "Sanuk"},
    {"TEVA", "Teva"},
    {"CHAC", "Chaco"},
    {"OOF", "OOFOS"},

    // === Nhóm 6: Thời trang Phổ thông & Cận Cao cấp (Mainstream & Accessible Luxury) === (20)
    {"ALDO", "ALDO"},
    {"SM", "Steve Madden"},
    {"NINE", "Nine West"},
    {"CK", "Charles & Keith"},
    {"PDRO", "Pedro"},
    {"LACO", "Lacoste"},
    {"TOMY", "Tommy Hilfiger"},
    {"CKLN", "Calvin Klein"},
    {"PRL", "Polo Ralph Lauren"},
    {"MK", "Michael Kors"},
    {"KATE", "Kate Spade New York"},
    {"TORY", "Tory Burch"},
    {"COAC", "Coach"},
    {"COLE", "Cole Haan"},
    {"JM", "Johnston & Murphy"},
    {"FLOR", "Florsheim"},
    {"KCOL", "Kenneth Cole"},
    {"VC", "Vince Camuto"},
    {"SE", "Sam Edelman"},
    {"GUES", "GUESS"},

    // === Nhóm 7: Thương hiệu Bền vững & Thân thiện Môi trường (Sustainable & Eco-Friendly) === (10)
    {"BIRD", "Allbirds"},
    {"VEJA", "Veja"},
    {"PGFA", "Patagonia Footwear"},
    {"POZU", "Po-Zu"},
    {"CARI", "Cariuma"},
    {"NONU", "Nothing New"},
    {"ETIK", "Etiko"},
    {"INDO", "Indosole"},
    {"SAOL", "SAOLA"},
    {"ROTH", "Rothys"},

    // === Nhóm 8: Thương hiệu Nhật Bản === (8)
    {"OT", "Onitsuka Tiger"},
    {"Y3", "Y-3 (Yohji Yamamoto x Adidas)"},
    {"VSVM", "Visvim"},
    {"CDGP", "Comme des Garçons PLAY"},
    {"BAPE", "A Bathing Ape (BAPE)"},
    {"RFW", "RFW Tokyo"},
    {"MOON", "Moonstar"},
    {"HEND", "Hender Scheme"},

    // === Nhóm 9: Thương hiệu Châu Âu (Anh, Ý, Pháp...) === (20)
    {"LOAK", "Loake Shoemakers"},
    {"CHEA", "Joseph Cheaney & Sons"},
    {"CHUR", "Churchs"},
    {"GREN", "Grenson"},
    {"TRCK", "Trickers"},
    {"BARK", "Barker England"},
    {"TODS", "Tods"},
    {"HOGN", "Hogan"},
    {"SANT", "Santoni"},
    {"MGNI", "Magnanni"},
    {"CARM", "Carmina Shoemaker"},
    {"LLOY", "LLOYD"},
    {"GABR", "Gabor"},
    {"SIOU", "Sioux"},
    {"REPE", "Repetto"},
    {"AMIP", "Ami Paris"},
    {"CPRO", "Common Projects"},
    {"GGDB", "Golden Goose"},
    {"FAGO", "Faguo"},
    {"ZESP", "Zespà"},

    // === Nhóm 10: Thương hiệu Xa xỉ (Luxury) === (25)
    {"GUCI", "Gucci"},
    {"BALC", "Balenciaga"},
    {"PRDA", "Prada"},
    {"LV", "Louis Vuitton"},
    {"LBTN", "Christian Louboutin"},
    {"CHOO", "Jimmy Choo"},
    {"AMQ", "Alexander McQueen"},
    {"VLNT", "Valentino Garavani"},
    {"YSL", "Saint Laurent"},
    {"VERS", "Versace"},
    {"FEND", "Fendi"},
    {"BVEN", "Bottega Veneta"},
    {"FERO", "Salvatore Ferragamo"},
    {"SROS", "Sergio Rossi"},
    {"GZAN", "Giuseppe Zanotti"},
    {"MBLK", "Manolo Blahnik"},
    {"BRLT", "Berluti"},
    {"JLOB", "John Lobb"},
    {"EGRN", "Edward Green"},
    {"FORD", "Tom Ford"},
    {"DIOR", "Dior"},
    {"CHAN", "Chanel"},
    {"HRMS", "Hermès"},
    {"CELN", "Celine"},
    {"GIVN", "Givenchy"},

    // === Nhóm 11: Bổ sung các thương hiệu khác === (15)
    {"HAVA", "Havaianas"},
    {"IPAN", "Ipanema"},
    {"GRDA", "Grendha"}, // **SỬA LỖI: Đã đổi ID từ GREN thành GRDA**
    {"CAMP", "Camper"},
    {"DIES", "Diesel"},
    {"GSTR", "G-Star RAW"},
    {"FP", "Fred Perry"},
    {"BSHR", "Ben Sherman"},
    {"PS", "Paul Smith"},
    {"EA", "Emporio Armani / EA7"},
    {"BOSS", "BOSS / HUGO"},
    {"TBAK", "Ted Baker"},
    {"KGEI", "Kurt Geiger"},
    {"AQUA", "Aquatalia"},
    {"SW", "Stuart Weitzman"},

    // === Nhóm 12: Bổ sung thêm cho đủ 200 === (27)
    {"ARCT", "Arcteryx"},
    {"ASOL", "Asolo"},
    {"BALY", "Bally"},
    {"CAT", "Caterpillar"},
    {"DIAD", "Diadora"},
    {"DUNL", "Dunlop"},
    {"EVIS", "Evisu"},
    {"GANT", "Gant"},
    {"HTEC", "Hi-Tec"},
    {"HUMM", "Hummel"},
    {"JJ", "Jack & Jones"},
    {"JMW", "J.M. Weston"},
    {"KAPA", "Kappa"},
    {"KARH", "Karhu"},
    {"KICK", "Kickers"},
    {"LOTO", "Lotto"},
    {"MEIN", "Meindl"},
    {"NROK", "New Rock"},
    {"PARA", "Paraboot"},
    {"PEPE", "Pepe Jeans"},
    {"PCAR", "Pierre Cardin"},
    {"PIKO", "Pikolinos"},
    {"RIDR", "Rider"},
    {"RMW", "R.M. Williams"},
    {"SREL", "Sorel"},
    {"SDRY", "Superdry"},
    {"UMBR", "Umbro"}};
const char *country_of_origin[200] = {
    "Trung Quốc", "Việt Nam", "Ý", "Ấn Độ", "Indonesia", "Brazil", "Thổ Nhĩ Kỳ", "Mexico", "Pakistan", "Bồ Đào Nha", "Tây Ban Nha", "Đức", "Hoa Kỳ", "Anh", "Pháp", "Nhật Bản", "Hàn Quốc", "Thái Lan", "Campuchia", "Myanmar", "Bangladesh", "Srilanka", "Ai Cập", "Ethiopia", "Nam Phi", "Kenya", "Maroc", "Tunisia", "Romania", "Ba Lan", "Slovakia", "Cộng hòa Séc", "Hungary", "Ukraine", "Nga", "Belarus", "Serbia", "Bosnia và Herzegovina", "Croatia", "Slovenia", "Albania", "Macedonia", "Bulgaria", "Hy Lạp", "Áo", "Bỉ", "Hà Lan", "Thụy Sĩ", "Thụy Điển", "Na Uy", "Phần Lan", "Đan Mạch", "Canada", "Argentina", "Colombia", "Peru", "Chile", "Ecuador", "Venezuela", "Uruguay", "Paraguay", "Bolivia", "Cuba", "Dominican Republic", "Haiti", "Guatemala", "Honduras", "El Salvador", "Nicaragua", "Costa Rica", "Panama", "Úc", "New Zealand", "Fiji", "Papua New Guinea", "Philippines", "Malaysia", "Singapore", "Đài Loan", "Hồng Kông", "Các Tiểu Vương quốc Ả Rập Thống nhất", "Ả Rập Xê Út", "Iran", "Israel", "Jordan", "Lebanon", "Syria", "Iraq", "Afghanistan", "Kazakhstan", "Uzbekistan", "Kyrgyzstan", "Tajikistan", "Turkmenistan", "Azerbaijan", "Armenia", "Georgia", "Mongolia", "Nepal", "Bhutan", "Lào", "Brunei", "Đông Timor"};
const char *color[200] = {
    "Black", "White", "Gray", "Brown", "Navy", "Red", "Blue", "Green", "Pink", "Yellow", "Orange", "Purple", "Beige", "Cream", "Khaki", "Olive", "Burgundy", "Maroon", "Teal", "Turquoise", "Aqua", "Coral", "Peach", "Mustard", "Lime", "Forest Green", "Royal Blue", "Sky Blue", "Lavender", "Fuchsia", "Magenta", "Gold", "Silver", "Bronze", "Rose Gold", "Metallic", "Iridescent", "Clear", "Transparent", "Multi-color", "Rainbow", "Printed", "Patterned", "Animal Print", "Floral", "Camo", "Neon", "Pastel", "Off-white", "Charcoal", "Taupe", "Espresso", "Cognac", "Stone", "Dusty Pink", "Mint Green", "Periwinkle", "Crimson", "Scarlet", "Cerulean", "Denim Blue", "Emerald", "Jade", "Ruby", "Sapphire", "Amethyst", "Topaz", "Copper", "Pewter", "Gunmetal", "Matte Black", "Glossy Black", "Patent Leather Black", "Distressed Brown", "Suede Brown", "Nubuck Black", "Canvas White", "Knit Gray", "Mesh Red", "Leather Blue", "Vegan Leather Green", "Synthetic Pink", "Rubber Yellow", "Velvet Purple", "Glitter Gold", "Sequin Silver", "Rhinestone Clear", "Embroidered Beige", "Reflective Gray", "Two-tone", "Three-tone", "Gradient", "Ombre", "Speckled", "Splatter", "Striped", "Plaid", "Houndstooth", "Geometric", "Abstract", "Ombré Blue", "Ombré Red", "Speckled White", "Splatter Black", "Striped Black and White", "Plaid Red and Black", "Houndstooth Gray", "Geometric Blue", "Abstract Multi", "Camo Green", "Leopard Print", "Zebra Print", "Snake Print", "Tiger Print", "Croc Print", "Paisley", "Polka Dot", "Checkered", "Gingham", "Floral Print"};
const char *size[100] = {
    "5", "5.5", "6", "6.5", "7", "7.5", "8", "8.5", "9", "9.5", "10", "10.5", "11", "11.5", "12", "12.5", "13", "13.5", "14", "15", "35", "35.5", "36", "36.5", "37", "37.5", "38", "38.5", "39", "39.5", "40", "40.5", "41", "41.5", "42", "42.5", "43", "43.5", "44", "44.5", "45", "45.5", "46", "46.5", "47", "47.5", "48", "48.5", "49", "50", "3", "3.5", "4", "4.5", "5", "5.5", "6", "6.5", "7", "7.5", "8", "8.5", "9", "9.5", "10", "10.5", "11", "11.5", "12", "13", "22", "22.5", "23", "23.5", "24", "24.5", "25", "25.5", "26", "26.5", "27", "27.5", "28", "28.5", "29", "29.5", "30", "1Y", "2Y", "3Y", "4Y", "5Y", "5C", "6C", "7C", "8C"};
const char *brand_description[20] = {
    "A global leader in athletic footwear, blending innovative technology with iconic designs for peak performance and style.", "Driven by a passion for sport, Adidas creates cutting-edge shoes that combine athletic prowess with trendsetting fashion.", "Known for its bold designs and athletic heritage, Puma offers stylish and performance-driven footwear for athletes and fashion enthusiasts alike.", "Focusing on comfort and quality craftsmanship, New Balance delivers reliable athletic and lifestyle shoes with a timeless appeal.", "An enduring classic, Converse provides versatile, iconic canvas sneakers that embody casual cool and individual expression.", "The authentic original for skate culture, Vans offers durable, stylish shoes with signature waffle outsoles, perfect for active lifestyles.", "Recognized for their rebellious spirit and unmistakable durability, Dr. Martens boots offer comfort, iconic style, and a rugged edge.", "Crafted for outdoor adventures and urban exploration, Timberland footwear combines rugged durability with timeless utility and style.", "Famous for luxurious comfort, Ugg boots and slippers provide unparalleled warmth and coziness, becoming a staple for relaxed style.", "Offering innovative comfort technologies, Skechers provides a wide range of stylish and comfortable shoes for every activity and age.", "Revolutionizing running with maximum cushioning, Hoka shoes deliver exceptional comfort and support for long distances and varied terrains.", "Synonymous with ergonomic comfort, Birkenstock sandals and clogs offer anatomically shaped footbeds for natural support and well-being.", "A symbol of Italian luxury, Gucci footwear showcases exquisite craftsmanship, bold designs, and iconic motifs for the discerning fashionista.", "Instantly recognizable by their signature red soles, Christian Louboutin heels epitomize high-fashion glamour, allure, and daring design.", "Pioneering sustainable footwear, Allbirds creates comfortable and minimalist shoes from natural, eco-friendly materials like wool and tree fiber."};
const char *product_name[200] = {
    "Velocity Rush", "Apex Stride", "Quantum Glide", "Hyperion Dash", "Aero-Pulse",
    "Surge Pro X", "Kinetic Flow", "Momentum Knit", "Impulse Runner", "StrideFlex 360",
    "Zenith Racer", "Nova-Charge", "Volt-Edge", "Echo Runner", "Apex Predator",
    "Fusion-Lite", "Grid Runner", "Solar-Sprint", "Velocity 2.0", "Power-Stride",
    "Aero-Max", "Swift-Core", "Element Racer", "The Accelerator", "Stratus-Fly",
    "Pulse-Ignite", "Apex Flow", "Hyper-Glide", "Quantum-X", "Surge-Tech",
    "Kinetic Pro", "Momentum Vibe", "Impulse Elite", "Stride-Zero", "Zenith Air",
    "Nova-React", "Volt-Force", "Echo-Shift", "Apex-Launch", "Fusion-Jet",
    "Grid-Lock", "Solar-Flare", "Velocity Max", "Power-Core", "Aero-Shift",
    "Swift-X Pro", "Element-Knit", "The Catalyst", "Stratus-Pro", "Pulse-X",
    "Metro-Grid", "Urban Nomad", "City-Vibe Lo", "The Originator", "Downtown Knit",
    "Nexus Form", "Street-Craft", "Concrete Roamer", "District Runner", "The Monarch",
    "Heritage-Lite", "Structure-X", "City-Scape", "Urban-Flow", "Axis Low",
    "The Collective", "Pavement Glide", "Metro-Shift", "Urban-Core", "City-Drift",
    "The Classic 88", "Downtown-Arch", "Nexus-Knit", "Street-Form", "Concrete-Pulse",
    "District-Lo", "The Sovereign", "Heritage-Pro", "Structure-Knit", "City-Bound",
    "Urban-Vibe", "Axis-Pro", "The Assemble", "Pavement-Strider", "Metro-Trek",
    "Urban-Frame", "City-Walk", "The Founder", "Downtown-X", "Nexus-Arch",
    "Street-Legend", "Concrete-Flow", "District-Hi", "The Icon", "Heritage-X",
    "Structure-Lo", "City-Pulse", "Urban-Knit", "Axis-Form", "The Standard",
    "Terra-Trek", "Ridge-Runner", "Summit-Ascent", "Geo-Pathfinder", "Canyon-Grip",
    "Trail-Core Pro", "Forest-Strider", "Granite-Guard", "Mesa-Hiker", "The Voyager",
    "Boulder-Dash", "River-Stone", "Path-Seeker", "Geo-Traction", "Crest-Walker",
    "Terra-Guard", "Ridge-Line", "Summit-Peak", "Geo-Frame", "Canyon-Explorer",
    "Trail-Force", "Forest-Roamer", "Granite-Tread", "Mesa-Drifter", "The Nomad",
    "Boulder-Grip", "River-Flow", "Path-Breaker", "Geo-Hiker", "Crest-Line",
    "Terra-Shift", "Ridge-Pro", "Summit-X", "Geo-Core", "Canyon-Trail",
    "Trail-Hunter", "Forest-Path", "Granite-X", "Mesa-Trail", "The Wanderer",
    "Boulder-Trek", "River-Tread", "Path-Guard", "Geo-Ascent", "Crest-Hiker",
    "Terra-Roam", "Ridge-Grip", "Summit-Lite", "Geo-Tread", "Canyon-Roamer",
    "The Heritage One", "Classic Stride", "Legend Loafer", "Essential Form", "Pure Walker",
    "The Ace 78", "Sovereign Knit", "Legacy Court", "The Standard Lo", "Union-Walker",
    "Parker Lo", "The Artisan", "Charter-Knit", "Estate-Runner", "The Original",
    "Heritage-Knit", "Classic-Form", "Legend-Pro", "Essential-Arch", "Pure-Stride",
    "The Ace-Hi", "Sovereign-Lo", "Legacy-Pro", "The Standard-Knit", "Union-Street",
    "Parker-Hi", "The Craftsman", "Charter-Lo", "Estate-Walker", "The Foundation",
    "Heritage-Arch", "Classic-Knit", "Legend-Court", "Essential-Pro", "Pure-Form",
    "The Ace-Knit", "Sovereign-Arch", "Legacy-One", "The Standard-Arch", "Union-Knit",
    "Parker-Pro", "The Creator", "Charter-Arch", "Estate-Form", "The Benchmark",
    "Heritage-Form", "Classic-Arch", "Legend-Knit", "Essential-Knit", "Pure-Arch"};
const char *material[200] = {
    "Full-Grain Leather", "Premium Suede", "Engineered Mesh", "Heavy-Duty Canvas", "Nubuck Leather",
    "Vegan Leather", "Ripstop Nylon", "PrimeKnit Fabric", "Patent Leather", "Organic Cotton",
    "Ballistic Mesh", "EVA Foam", "Vulcanized Rubber", "GORE-TEX Membrane", "Calfskin Leather",
    "Merino Wool", "Microfiber Suede", "TPU Exoskeleton", "Denim Twill", "Flyknit Upper",
    "Pebbled Leather", "Natural Crepe Sole", "Spacer Mesh", "Cordura Fabric", "Lambskin Lining",
    "Recycled PET", "Oiled Leather", "Gum Rubber Outsole", "Polar-Fleece", "Tumbled Leather",
    "Synthetic Nubuck", "Air-Mesh", "Hemp Canvas", "Memory Foam Insole", "Waterproof Suede",
    "Polyurethane (PU)", "Jacquard Weave", "Carbon Fiber Plate", "Faux Fur Lining", "Neoprene",
    "Washed Canvas", "Suede-Tex", "Vibram Outsole", "Perforated Leather", "TechLoom Knit",
    "Distressed Leather", "Cotton Terry", "HyperWeave", "Cork Midsole", "Aniline Leather",
    "Synthetic Mesh", "Brushed Suede", "Latex Foam", "Ripstop Canvas", "Alcantara Fabric",
    "Pigskin Leather", "Power-Knit", "Transparent TPU", "Velvet Upper", "Grid-Mesh",
    "Eco-Leather", "Dynamic Weave", "Herringbone Twill", "Tweed Fabric", "Cushioned EVA",
    "Waxy Commander Leather", "Aero-Mesh Pro", "Soft-Touch Nubuck", "Ortholite Sockliner", "Bonded Leather",
    "Flex-Weave", "Spacer-Knit", "High-Abrasion Rubber", "Corduroy", "Kangaroo Leather",
    "Durable Ripstop", "3D-Knit Upper", "Faux Snake Skin", "Insulated Thinsulate", "Split-Grain Suede",
    "Breathable Linen", "Lightweight EVA", "Shock-Absorbing Gel", "Grained Leather", "Stretch-Knit",
    "HydroGuard Waterproofing", "Embossed Leather", "Canvas Duck", "Lycra Spandex", "Perforated Suede",
    "Laser-Etched Leather", "Structured Felt", "Molded Rubber", "Woven Textile", "CoolMax Fabric",
    "Reflective Nylon", "Micro-Suede", "Dual-Density Foam", "Satin Finish", "Eco-Canvas",
    "Chrome-Free Leather", "Matrix-Weave", "Bamboo Fabric", "Faux Crocodile", "Thermal Lining",
    "Nappa Leather", "Ultra-Knit", "Closed-Cell Foam", "Glitter Fabric", "Plant-Based Leather",
    "Shearling Lining", "Woven Leather", "High-Density EVA", "Holographic PU", "Pony Hair Leather",
    "Brushed-Canvas", "Diamond-Grid Mesh", "Soft-Shell Fabric", "Vegan Suede", "Metallic Leather",
    "Textured Knit", "Natural Cork Footbed", "Algae Bloom Foam", "Water-Repellent Nylon", "Coated Canvas",
    "Saffiano Leather", "Honeycomb Mesh", "Synthetic Patent", "Flannel Lining", "Bio-Foam",
    "Cracked Leather", "Mesh-Fusion", "Recycled Rubber", "Tencel Lyocell", "Goatskin Leather",
    "Stretch Canvas", "Engineered Suede", "TPU Heel Counter", "Knit-Mesh Hybrid", "Matte Leather",
    "Woven Raffia", "Carbon-Infused Rubber", "Quilted Nylon", "Eco-Microfiber", "Deerskin",
    "Digital-Print Canvas", "Fly-Weave", "Molded EVA Footbed", "Croc-Embossed Leather", "Ripstop-Mesh",
    "Italian Suede", "Knit-Lockdown Upper", "Phylon Midsole", "Stretch-Suede", "Vachetta Leather",
    "Weathered Leather", "Performance-Knit", "TPU Film Overlay", "Faux Ostrich", "Dri-Fit Lining",
    "Top-Grain Leather", "Adaptive-Knit", "Recycled Foam", "Textured PU", "Horsehide Leather",
    "Seamless Upper", "Cushion-Soft Foam", "Woven-Strap", "Mirror-Finish Leather", "Dynamic-Mesh",
    "Plant-Dyed Canvas", "Energy-Return Foam", "Structured Nylon", "Vegan-Wool", "Burnished Leather"};
const char *description_product[200] = {
    "Tái định nghĩa phong cách đường phố. Thiết kế tối giản kết hợp cùng vật liệu cao cấp mang lại vẻ ngoài hiện đại và tinh tế.",
    "Dành cho những vận động viên thực thụ. Công nghệ đế giữa hoàn trả năng lượng giúp bạn bứt phá trong từng sải chân.",
    "Vẻ đẹp vượt thời gian. Được chế tác thủ công từ da bê nguyên tấm, đôi giày này là biểu tượng của sự sang trọng và đẳng cấp.",
    "Người bạn đồng hành trên mọi nẻo đường. Đế ngoài Vibram siêu bám và lớp màng chống thấm giúp bạn chinh phục mọi địa hình.",
    "Sự thoải mái tuyệt đối cho mỗi ngày. Lớp lót memory foam ôm trọn bàn chân, mang lại cảm giác êm ái suốt cả ngày dài.",
    "Thiết kế táo bạo dành cho người dẫn đầu. Những đường cắt cúp mạnh mẽ và phối màu độc đáo giúp bạn luôn nổi bật.",
    "Linh hoạt và nhẹ nhàng. Phần upper bằng vải dệt kim co giãn, thoáng khí, mang lại sự vừa vặn hoàn hảo như một chiếc tất.",
    "Nâng tầm trang phục công sở của bạn. Kiểu dáng Oxford cổ điển kết hợp cùng chất da bóng bẩy tạo nên vẻ ngoài lịch lãm.",
    "Sự lựa chọn hoàn hảo cho mùa hè. Thiết kế sandal thoáng mát cùng chất liệu nhanh khô, lý tưởng cho những chuyến đi biển.",
    "Bền bỉ vượt trội. Được làm từ vải Cordura chống mài mòn và kháng nước, sẵn sàng cho những thử thách khắc nghiệt nhất.",
    "Phong cách vintage trở lại. Thiết kế lấy cảm hứng từ thập niên 90, mang đến nét hoài cổ nhưng vẫn rất thời thượng.",
    "Sự kết hợp hoàn hảo giữa thể thao và thời trang. Bạn có thể tự tin mang đôi giày này từ phòng gym đến các buổi dạo phố.",
    "Thân thiện với môi trường. Sản phẩm được làm từ vật liệu tái chế, một bước tiến nhỏ cho một hành tinh xanh hơn.",
    "Cảm nhận sự khác biệt. Đế giữa EVA siêu nhẹ giúp giảm tối đa trọng lượng, cho bước đi nhẹ như không.",
    "Được tạo ra để vận động. Cấu trúc giày hỗ trợ tối đa cho các chuyển động ngang, lý tưởng cho các buổi tập cường độ cao.",
    "Một tuyên ngôn về phong cách cá nhân. Hãy để đôi chân bạn lên tiếng với thiết kế độc đáo này.",
    "Sự tinh túy của chủ nghĩa tối giản. Mọi chi tiết thừa đều được loại bỏ, chỉ giữ lại những gì cần thiết cho một thiết kế hoàn mỹ.",
    "Giữ ấm cho mùa đông. Lớp lót lông cừu mềm mại và khả năng chống thấm nước giúp đôi chân bạn luôn ấm áp và khô ráo.",
    "Tỏa sáng trong từng bước đi. Các chi tiết ánh kim và vật liệu phản quang tạo nên hiệu ứng bắt mắt dưới ánh đèn.",
    "Sự lựa chọn của các nhà vô địch. Đôi giày này đã đồng hành cùng nhiều vận động viên trên bục vinh quang.",
    "Thiết kế liền mạch không đường may, giảm tối đa ma sát và mang lại sự thoải mái vượt trội.",
    "Đế giày platform cá tính giúp tăng chiều cao một cách tinh tế và thể hiện phong cách sành điệu.",
    "Lấy cảm hứng từ những đôi giày bóng rổ cổ điển, mang lại vẻ ngoài năng động và khỏe khoắn.",
    "Chất liệu da lộn cao cấp mang lại vẻ mềm mại, sang trọng và cần được chăm sóc đặc biệt.",
    "Công nghệ thoáng khí 360 độ giúp đôi chân luôn mát mẻ, ngay cả trong những ngày hè nóng nực.",
    "Sẵn sàng cho một ngày làm việc hiệu quả. Thiết kế hỗ trợ vòm chân giúp giảm mỏi khi phải đứng hoặc đi lại nhiều.",
    "Đế ngoài được thiết kế với các rãnh xẻ sâu tăng cường độ linh hoạt cho bàn chân.",
    "Một tác phẩm nghệ thuật thực thụ. Mỗi đường kim mũi chỉ đều thể hiện sự tỉ mỉ và tay nghề của người thợ thủ công.",
    "Phong cách preppy thanh lịch. Kiểu dáng giày lười dễ dàng kết hợp với quần chinos và áo polo.",
    "Khả năng chống trơn trượt tuyệt vời, đảm bảo an toàn trên các bề mặt ẩm ướt.",
    "Thiết kế bất đối xứng độc đáo, phá vỡ mọi quy tắc thời trang thông thường.",
    "Hệ thống dây buộc thông minh giúp tùy chỉnh độ ôm một cách nhanh chóng và dễ dàng.",
    "Cảm giác tự do như đi chân trần, nhưng vẫn được bảo vệ an toàn.",
    "Màu sắc trung tính dễ phối đồ, là một item không thể thiếu trong tủ giày của bạn.",
    "Công nghệ in 3D tạo nên những chi tiết trang trí phức tạp và cấu trúc giày siêu nhẹ.",
    "Sự êm ái đến từ lớp đệm gel ở gót chân, hấp thụ tối đa chấn động.",
    "Thiết kế cổ cao (high-top) giúp bảo vệ và hỗ trợ cổ chân hiệu quả.",
    "Vẻ ngoài bụi bặm, phong trần với chất liệu da sáp và các chi tiết bằng đồng.",
    "Thoải mái ngay từ lần xỏ chân đầu tiên, không cần thời gian break-in.",
    "Hãy để sự sáng tạo dẫn lối với phiên bản giày có thể tùy chỉnh màu sắc theo ý thích.",
    "Sự cân bằng hoàn hảo giữa hiệu năng và thẩm mỹ.",
    "Được thiết kế để chịu được sự khắc nghiệt của sân tập và sự hối hả của đường phố.",
    "Vật liệu co giãn 4 chiều cho phép bàn chân chuyển động một cách tự nhiên nhất.",
    "Một lựa chọn thông minh cho những chuyến du lịch, vừa nhẹ nhàng vừa phong cách.",
    "Đế giày cao su tự nhiên mang lại độ bền và độ bám dính vượt trội.",
    "Thiết kế slip-on tiện lợi, dễ dàng mang vào và tháo ra.",
    "Lớp phủ chống bám bẩn giúp việc vệ sinh giày trở nên dễ dàng hơn bao giờ hết.",
    "Mang cả thiên nhiên vào trong thiết kế với các họa tiết hoa lá tinh tế.",
    "Cấu trúc siêu nhẹ, là vũ khí bí mật giúp bạn về đích nhanh hơn.",
    "Sự sang trọng thầm lặng, không phô trương nhưng vẫn đầy cuốn hút.",
    "Đôi giày của tương lai, với thiết kế đột phá và công nghệ tiên tiến.",
    "Sự trở lại của một huyền thoại, được tái sinh với những cải tiến hiện đại.",
    "Đơn giản là đẹp. Thiết kế gọn gàng, phù hợp với mọi hoàn cảnh.",
    "Đế giày chống dầu và hóa chất, đảm bảo an toàn trong môi trường làm việc đặc thù.",
    "Phần gót giày được gia cố để tăng cường sự ổn định và hỗ trợ.",
    "Lưỡi gà và cổ giày có đệm mút dày dặn mang lại cảm giác thoải mái tối đa.",
    "Được kiểm nghiệm bởi các vận động viên hàng đầu thế giới.",
    "Sự hòa quyện giữa nét cổ điển và những điểm nhấn hiện đại.",
    "Mũi giày được bọc cao su để tăng độ bền và bảo vệ ngón chân.",
    "Đường chỉ may tương phản tạo nên điểm nhấn tinh tế cho thiết kế.",
    "Thoáng khí và nhanh khô, lý tưởng cho các hoạt động dưới nước.",
    "Một đôi giày đa năng, sẵn sàng cùng bạn đi bất cứ đâu.",
    "Cảm nhận sự mềm mại của lớp lót da cừu cao cấp.",
    "Thiết kế tối ưu hóa cho việc chạy đường dài, giảm thiểu tác động lên khớp.",
    "Phong cách unisex, phù hợp cho cả nam và nữ.",
    "Logo được dập chìm tinh tế, khẳng định đẳng cấp thương hiệu.",
    "Hệ thống rãnh thoát nước ở đế ngoài giúp bạn tự tin di chuyển trên bề mặt ướt.",
    "Chất da sẽ càng đẹp hơn theo thời gian, tạo nên dấu ấn cá nhân độc đáo.",
    "Kết cấu vững chắc mang lại sự tự tin trong từng bước đi.",
    "Một item chủ đạo giúp nâng tầm bất kỳ bộ trang phục nào.",
    "Công nghệ khử mùi giúp đôi chân luôn thơm tho, sạch sẽ.",
    "Dễ dàng gấp gọn, tiết kiệm không gian cho hành lý của bạn.",
    "Được làm từ một tấm da duy nhất, tạo nên sự liền mạch và đẳng cấp.",
    "Trọng lượng siêu nhẹ, hiệu năng siêu khủng.",
    "Màu sắc được lấy cảm hứng từ vẻ đẹp của thiên nhiên.",
    "Sự đầu tư xứng đáng cho phong cách và sự thoải mái của bạn.",
    "Phá vỡ giới hạn với đế giày có độ đàn hồi cao.",
    "Kiểu dáng ôm sát, tôn lên vẻ đẹp của đôi chân.",
    "Thiết kế mạnh mẽ, thể hiện tinh thần không ngừng tiến về phía trước.",
    "Lớp đệm khí trải dài từ gót đến mũi, cho trải nghiệm êm ái toàn diện.",
    "Hãy để đôi giày này kể câu chuyện của riêng bạn.",
    "Sự lựa chọn của những người yêu thích sự dịch chuyển.",
    "Vẻ đẹp mộc mạc của vật liệu tự nhiên.",
    "Được thiết kế để tồn tại cùng thời gian, cả về kiểu dáng lẫn chất lượng.",
    "Sự thoải mái bắt đầu từ những điều nhỏ nhất.",
    "Kết hợp giữa nghệ thuật thủ công truyền thống và công nghệ sản xuất hiện đại.",
    "Đế ngoài trong suốt độc đáo, để lộ bộ đệm công nghệ bên trong.",
    "Sự thanh lịch đến từ những chi tiết tối giản nhất.",
    "Cấu trúc hỗ trợ bàn chân, giúp phân bổ đều trọng lượng cơ thể.",
    "Thiết kế dành riêng cho khí hậu nóng ẩm, tối đa hóa sự thoáng khí.",
    "Một chút hoang dã với họa tiết da báo cá tính.",
    "Đôi giày này là tấm vé đưa bạn đến với những cuộc phiêu lưu mới.",
    "Sự mềm mại và linh hoạt cho những bước nhảy tự do.",
    "Được chế tác bởi những đôi bàn tay khéo léo nhất.",
    "Nâng niu từng bước chân của bạn.",
    "Sự lựa chọn không thể sai lầm cho một ngày cuối tuần năng động.",
    "Vượt qua mọi giới hạn với một thiết kế không giới hạn.",
    "Tuyên ngôn thời trang của thế hệ mới.",
    "Sự sang trọng không cần gắng gượng.",
    "Được tạo ra để ghi dấu ấn.",
    "Khi hiệu suất và phong cách là một.",
    "Đơn giản nhưng không hề đơn điệu.",
    "Cảm hứng từ kiến trúc đô thị hiện đại.",
    "Bước đi nhẹ nhàng, tự tin tiến bước.",
    "Đôi giày hoàn hảo để bắt đầu một ngày mới.",
    "Thiết kế mang tính biểu tượng, được yêu thích qua nhiều thế hệ.",
    "Sự thoải mái mà bạn có thể cảm nhận rõ rệt.",
    "Được tạo ra cho những khoảnh khắc đáng nhớ.",
    "Chất lượng làm nên sự khác biệt.",
    "Phong cách của bạn, quy tắc của bạn.",
    "Được thiết kế để chuyển động cùng bạn.",
    "Sự tinh tế trong từng chi tiết.",
    "Một bước đột phá trong công nghệ giày thể thao.",
    "Vẻ đẹp của sự không hoàn hảo trong chất liệu da tự nhiên.",
    "Hãy sẵn sàng để chinh phục thế giới.",
    "Đôi giày nói lên bạn là ai.",
    "Sự tự tin đến từ sự thoải mái.",
    "Thiết kế cổ điển được làm mới với những chi tiết bất ngờ.",
    "Mang lại năng lượng cho mỗi bước đi của bạn.",
    "Được tạo ra để thách thức những điều không thể.",
    "Sự lựa chọn của những người sành điệu.",
    "Vẻ đẹp vượt qua mọi xu hướng.",
    "Được thiết kế để bảo vệ đôi chân bạn một cách tối ưu.",
    "Một phong cách sống, không chỉ là một đôi giày.",
    "Sự hoàn hảo trong từng đường nét.",
    "Cảm nhận sự vững chãi trên mọi bề mặt.",
    "Thiết kế dành cho những tâm hồn tự do.",
    "Khi sự bền bỉ gặp gỡ phong cách.",
    "Đôi giày sẽ cùng bạn viết nên những câu chuyện mới.",
    "Sự thoải mái sang trọng cho đôi chân.",
    "Được tạo ra để truyền cảm hứng.",
    "Phong cách vượt trội, hiệu năng đỉnh cao.",
    "Thiết kế tối giản cho cuộc sống hiện đại.",
    "Một biểu tượng của sự đổi mới.",
    "Vẻ đẹp đến từ những điều giản dị.",
    "Được tạo ra để bạn luôn dẫn đầu.",
    "Sự kết hợp giữa sức mạnh và sự thanh lịch.",
    "Đôi giày mà bạn sẽ không muốn cởi ra.",
    "Thiết kế cho những cuộc hành trình không hồi kết.",
    "Khi mỗi chi tiết đều mang một ý nghĩa.",
    "Sự thoải mái được ưu tiên hàng đầu.",
    "Được chế tác để trở thành một phần của bạn.",
    "Phong cách không chỉ là những gì bạn mặc, mà là cách bạn sống.",
    "Được tạo ra để di chuyển không ngừng.",
    "Sự tinh xảo trong từng đường may.",
    "Công nghệ tiên tiến cho hiệu suất vượt trội.",
    "Vẻ đẹp tự nhiên của da nguyên tấm.",
    "Hãy tạo ra con đường của riêng bạn.",
    "Sự tự tin tuyệt đối trong từng chuyển động.",
    "Thiết kế vượt thời gian cho tủ đồ của bạn.",
    "Mang lại nguồn năng lượng tích cực mỗi ngày.",
    "Được tạo ra để phá vỡ mọi quy luật.",
    "Sự lựa chọn của những người có gu.",
    "Vẻ đẹp không bao giờ phai mờ.",
    "Được thiết kế để bảo vệ tài sản quý giá nhất của bạn: đôi chân.",
    "Một phong cách sống năng động và tích cực.",
    "Sự hoàn hảo trong từng góc cạnh.",
    "Cảm nhận sự ổn định và cân bằng tuyệt đối.",
    "Thiết kế dành cho những người yêu tự do và phiêu lưu.",
    "Khi độ bền và phong cách song hành.",
    "Đôi giày sẽ là người bạn đồng hành đáng tin cậy.",
    "Sự sang trọng và thoải mái trong một thiết kế.",
    "Được tạo ra để khơi nguồn sáng tạo.",
    "Phong cách đỉnh cao, hiệu năng không đối thủ.",
    "Thiết kế tối giản cho người yêu sự tinh tế.",
    "Một biểu tượng của sự sáng tạo không ngừng.",
    "Vẻ đẹp tiềm ẩn trong những chi tiết đơn giản.",
    "Được tạo ra để bạn luôn là người tiên phong.",
    "Sự kết hợp hoàn hảo giữa sức mạnh và vẻ đẹp.",
    "Đôi giày mà bạn sẽ yêu ngay từ cái nhìn đầu tiên.",
    "Thiết kế cho những hành trình khám phá bản thân.",
    "Khi mỗi chi tiết đều được chăm chút kỹ lưỡng.",
    "Sự thoải mái là nền tảng của mọi thứ.",
    "Được chế tác để hòa hợp với từng chuyển động của bạn.",
    "Phong cách là cách bạn thể hiện mình mà không cần lời nói.",
    "Tối ưu cho sự vận động liên tục.",
    "Đường nét tinh xảo, chất liệu cao cấp.",
    "Công nghệ tương lai, ngay hôm nay.",
    "Vẻ đẹp của da thật và những vết xước của thời gian.",
    "Hãy tự tin bước đi và chinh phục ước mơ.",
    "Sự chắc chắn trong từng bước chân.",
    "Thiết kế vượt thời gian, dành cho những người có giá trị bền vững.",
    "Năng lượng cho một ngày mới, bắt đầu từ đôi chân.",
    "Dám khác biệt, dám dẫn đầu.",
    "Sự lựa chọn hàng đầu của những người am hiểu thời trang.",
    "Vẻ đẹp thách thức thời gian.",
    "Được thiết kế để bảo vệ và nâng niu.",
    "Không chỉ là một đôi giày, đó là một tuyên ngôn.",
    "Sự hoàn hảo đến từ sự đơn giản.",
    "Cảm nhận sự kết nối với mặt đất.",
    "Thiết kế dành cho những tâm hồn không chịu ngồi yên."};
// Mảng cho feedback
const char *feedback_content[20] = {
    "Sản phẩm rất tốt, đúng như mô tả",
    "Chất lượng tuyệt vời, đáng đồng tiền",
    "Giao hàng nhanh, đóng gói cẩn thận",
    "Giày đẹp, form vừa vặn",
    "Hài lòng với sản phẩm",
    "Chất lượng ổn, giá cả hợp lý",
    "Sẽ ủng hộ shop lần sau",
    "Đáng mua, recommended!",
    "Chất lượng khá tốt",
    "Đẹp như hình, worth it",
    "Không được như mong đợi",
    "Cần cải thiện chất lượng",
    "Hơi đắt so với chất lượng",
    "Size hơi rộng",
    "Màu sắc không giống hình",
    "Giao hàng hơi chậm",
    "Chất liệu tạm được",
    "Có thể tốt hơn",
    "Bình thường",
    "Cần cải thiện dịch vụ"};

// Mảng cho trạng thái đơn hàng
const char *order_status[5] = {
    "Pending",
    "Processing",
    "Shipped",
    "Delivered",
    "Cancelled"};

// Mảng cho phương thức thanh toán
const char *payment_methods[5] = {
    "Cash",
    "Credit Card",
    "Bank Transfer",
    "E-wallet",
    "PayPal"};

// Mảng cho trạng thái thanh toán
const char *payment_status[3] = {
    "Pending",
    "Completed",
    "Failed"};
/**
 * @brief Tạo và trả về một SĐT ngẫu nhiên có đầu số Việt Nam.
 * Hàm này sử dụng một bộ đệm tĩnh (static).
 * !! CẢNH BÁO: Hàm không an toàn khi gọi nhiều lần trong cùng một biểu thức.
 * @return Con trỏ (char*) tới một chuỗi SĐT.
 */
char *gen_phone_number()
{
    // Biến static chỉ được khởi tạo một lần và tồn tại suốt chương trình.
    static char sdt_buffer[11]; // 10 cho số, 1 cho ký tự '\0'

    sdt_buffer[0] = '0';

    // 4. Tạo 7 chữ số còn lại (vì đầu số đã có 3 chữ số)
    for (int i = 1; i < 10; i++)
    {
        sdt_buffer[i] = (rand() % 10) + '0';
    }

    // 5. Đảm bảo ký tự kết thúc chuỗi ở đúng vị trí cuối cùng
    sdt_buffer[10] = '\0';

    return sdt_buffer;
}

/**
 * @brief Tạo username ngẫu nhiên (6-10 ký tự chữ và số).
 * @return Con trỏ tới buffer tĩnh chứa username.
 */
char *gen_username()
{
    static char user_buffer[21]; // Tối đa 10 ký tự + '\0'
    const char *charset = "abcdefghijklmnopqrstuvwxyz0123456789";
    int charset_len = strlen(charset);

    int len = (rand() % 15) + 6; // Độ dài từ 6 đến 20
    for (int i = 0; i < len; i++)
    {
        user_buffer[i] = charset[rand() % charset_len];
    }
    user_buffer[len] = '\0'; // Đặt ký tự kết thúc

    return user_buffer;
}

/**
 * @brief Tạo password ngẫu nhiên mạnh (12-20 ký tự chữ, số, ký tự đặc biệt).
 * @return Con trỏ tới buffer tĩnh chứa password.
 */
char *gen_password()
{
    static char pass_buffer[21]; // Tối đa 20 ký tự + '\0'
    const char *charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@";
    int charset_len = strlen(charset);

    int len = (rand() % 12) + 8; // Độ dài từ 8 đến 20
    for (int i = 0; i < len; i++)
    {
        pass_buffer[i] = charset[rand() % charset_len];
    }
    pass_buffer[len] = '\0'; // Đặt ký tự kết thúc

    return pass_buffer;
}

/**
 * @brief Tạo email ngẫu nhiên đuôi @gmail.com. Hàm này tự tạo phần username.
 * @return Con trỏ tới buffer tĩnh chứa email.
 */
char *gen_email()
{
    static char email_buffer[41]; // Tối đa 30 ký tự + '\0'
    const char *charset = "abcdefghijklmnopqrstuvwxyz0123456789";
    const char *domain = "@gmail.com";
    int charset_len = strlen(charset);

    // Tự tạo phần username riêng
    int username_len = (rand() % 25) + 6; // Độ dài từ 6 đến 30
    for (int i = 0; i < username_len; i++)
    {
        email_buffer[i] = charset[rand() % charset_len];
    }

    // Nối đuôi domain vào
    strcpy(&email_buffer[username_len], domain);

    return email_buffer;
}

void gen_customer_id(int i)
{
    sprintf(customer_ids[i], "CUS%05d", i + 1);
}

void gen_product_id(int i)
{
    sprintf(product_ids[i], "PD%06d", i + 1);
}

void gen_variant_id(int i)
{
    sprintf(variant_ids[i], "V%07d", i + 1);
}

void gen_feedback_id(int i)
{
    sprintf(feedback_ids[i], "FB%06d", i + 1);
}

void gen_order_id(int i)
{
    sprintf(order_ids[i], "ORD%05d", i + 1);
}

void gen_orderdetail_id(int i)
{
    sprintf(orderdetail_ids[i], "OD%06d", i + 1);
}

void gen_employee_id(int i)
{
    sprintf(employee_ids[i], "EMP%05d", i + 1);
}

int main()
{
    // 1. Khởi tạo hạt giống cho bộ tạo số ngẫu nhiên
    // Chỉ cần gọi srand() một lần duy nhất khi bắt đầu chương trình.
    srand((unsigned int)time(NULL));
    FILE *filePointer; // Khai báo một con trỏ kiểu FILE

    // Mở file có tên "output.txt" ở chế độ ghi ("w").
    // Nếu file không tồn tại, nó sẽ được tạo mới.
    // Nếu file đã tồn tại, nội dung cũ sẽ bị ghi đè.
    filePointer = fopen("shoestore.sql", "w");

    // Kiểm tra xem file có mở thành công không
    if (filePointer == NULL)
    {
        printf("Không thể mở file.\n");
        return 1; // Trả về mã lỗi
    }

    // set UTF8
    fprintf(filePointer, "SET client_encoding TO 'UTF8';\n");

    // insert bảng customer
    fprintf(filePointer, "INSERT INTO customer(customer_id, first_name, last_name, address, city, district, phone_number, email, credit_card, dob, gender, username, password) VALUES\n");
    for (int i = 0; i < 100; i++)
    {
        gen_customer_id(i);
        // cuối dòng là dấu ,
        if (i != 99)
            fprintf(filePointer, "('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'),\n" /*dấu , cuối dòng*/,
                    customer_ids[i], first_name[random_int(0, 199)], last_name[random_int(0, 199)],
                    address[random_int(0, 199)], city[random_int(0, 199)], district[random_int(0, 199)],
                    gen_phone_number(), gen_email(), credit_card[random_int(0, 199)],
                    dob[random_int(0, 199)], gender[random_int(0, 1)], gen_username(), gen_password());

        // cuối dòng là dấu;
        else
            fprintf(filePointer, "('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');\n\n" /*dấu ; cuối dòng*/,
                    customer_ids[i], first_name[random_int(0, 199)], last_name[random_int(0, 199)],
                    address[random_int(0, 199)], city[random_int(0, 199)], district[random_int(0, 199)],
                    gen_phone_number(), gen_email(), credit_card[random_int(0, 199)],
                    dob[random_int(0, 199)], gender[random_int(0, 1)], gen_username(), gen_password());
    }

    // insert bảng category
    fprintf(filePointer, "INSERT INTO category(category_id, category_name) VALUES\n");
    for (int i = 0; i < 50; i++)
    {
        if (i != 49)
            fprintf(filePointer, "('%s','%s'),\n", categories[i][0], categories[i][1]);
        else
            fprintf(filePointer, "('%s','%s');\n\n", categories[i][0], categories[i][1]);
    }

    // insert bảng brand
    fprintf(filePointer, "INSERT INTO brand(brand_id, brand_name, country_of_origin, brand_description) VALUES\n");
    for (int i = 0; i < 20; i++)
    {
        if (i != 19)
            fprintf(filePointer, "('%s','%s', '%s', '%s'),\n", brands[i][0], brands[i][1], country_of_origin[random_int(0, 99)], brand_description[random_int(0, 14)]);
        else
            fprintf(filePointer, "('%s','%s', '%s', '%s');\n\n", brands[i][0], brands[i][1], country_of_origin[random_int(0, 99)], brand_description[random_int(0, 14)]);
    }

    // insert bảng product
    fprintf(filePointer, "INSERT INTO product(product_id, category_id, brand_id, product_name, purchase_price, selling_price, material, product_description) VALUES\n");
    for (int i = 0; i < 100; i++)
    {
        gen_product_id(i);
        double selling_price = random_double(10, 5000);
        double purchase_price = random_double(10, selling_price);
        if (i != 99)
            fprintf(filePointer, "('%s', '%s', '%s', '%s', '%.2lf', '%.2lf', '%s', '%s'),\n", product_ids[i], categories[random_int(0, 49)][0], brands[random_int(0, 199)][0], product_name[random_int(0, 99)], purchase_price, selling_price, material[random_int(0, 99)], description_product[random_int(0, 99)]);
        else
            fprintf(filePointer, "('%s', '%s', '%s', '%s', '%.2lf', '%.2lf', '%s', '%s');\n\n", product_ids[i], categories[random_int(0, 49)][0], brands[random_int(0, 199)][0], product_name[random_int(0, 99)], purchase_price, selling_price, material[random_int(0, 99)], description_product[random_int(0, 99)]);
    }

    // insert bảng variant
    fprintf(filePointer, "INSERT INTO variant(variant_id, product_id, color, size, stock_quantity) VALUES\n");
    for (int i = 0; i < 100; i++)
    {
        gen_variant_id(i);
        if (i != 99)
            fprintf(filePointer, "('%s','%s', '%s', '%s', '%d'),\n", variant_ids[i], product_ids[random_int(0, 999)], color[random_int(0, 99)], size[random_int(0, 50)], random_int(0, 10000));
        else
            fprintf(filePointer, "('%s','%s', '%s', '%s', '%d');\n\n", variant_ids[i], product_ids[random_int(0, 999)], color[random_int(0, 99)], size[random_int(0, 50)], random_int(0, 10000));
    }

    // Insert bảng employee
    fprintf(filePointer, "INSERT INTO employee(employee_id, first_name, last_name, dob, phone_number, email, username, password) VALUES\n");
    for (int i = 0; i < 50; i++)
    {
        gen_employee_id(i);
        if (i != 49)
            fprintf(filePointer, "('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'),\n",
                    employee_ids[i],
                    first_name[random_int(0, 199)],
                    last_name[random_int(0, 199)],
                    dob[random_int(0, 199)],
                    gen_phone_number(),
                    gen_email(),
                    gen_username(),
                    gen_password());
        else
            fprintf(filePointer, "('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');\n\n",
                    employee_ids[i],
                    first_name[random_int(0, 199)],
                    last_name[random_int(0, 199)],
                    dob[random_int(0, 199)],
                    gen_phone_number(),
                    gen_email(),
                    gen_username(),
                    gen_password());
    }

    // Insert bảng order
    fprintf(filePointer, "INSERT INTO \"order\"(order_id, customer_id, employee_id, total_amount, total_discount, final_amount, order_date, status, payment_method, payment_status, note) VALUES\n");
    for (int i = 0; i < 100; i++)
    {
        gen_order_id(i);
        double total_amount = random_double(100, 10000);
        double total_discount = random_double(0, total_amount * 0.3);
        double final_amount = total_amount - total_discount;

        if (i != 99)
            fprintf(filePointer, "('%s', '%s', '%s', '%.2f', '%.2f', '%.2f', '2023-%02d-%02d', '%s', '%s', '%s', 'Order #%d'),\n",
                    order_ids[i],
                    customer_ids[random_int(0, 99)],
                    employee_ids[random_int(0, 49)],
                    total_amount,
                    total_discount,
                    final_amount,
                    random_int(1, 12),
                    random_int(1, 28),
                    order_status[random_int(0, 4)],
                    payment_methods[random_int(0, 4)],
                    payment_status[random_int(0, 2)],
                    i + 1);
        else
            fprintf(filePointer, "('%s', '%s', '%s', '%.2f', '%.2f', '%.2f', '2023-%02d-%02d', '%s', '%s', '%s', 'Order #%d');\n\n",
                    order_ids[i],
                    customer_ids[random_int(0, 99)],
                    employee_ids[random_int(0, 49)],
                    total_amount,
                    total_discount,
                    final_amount,
                    random_int(1, 12),
                    random_int(1, 28),
                    order_status[random_int(0, 4)],
                    payment_methods[random_int(0, 4)],
                    payment_status[random_int(0, 2)],
                    i + 1);
    }

    // Insert bảng orderdetail
    fprintf(filePointer, "INSERT INTO orderdetail(orderdetail_id, order_id, variant_id, quantity, unit_price, discount, sub_total) VALUES\n");
    for (int i = 0; i < 200; i++)
    {
        gen_orderdetail_id(i);
        int quantity = random_int(1, 5);
        double unit_price = random_double(50, 500);
        double discount = random_double(0, unit_price * 0.2);
        double sub_total = quantity * (unit_price - discount);

        if (i != 199)
            fprintf(filePointer, "('%s', '%s', '%s', '%d', '%.2f', '%.2f', '%.2f'),\n",
                    orderdetail_ids[i],
                    order_ids[random_int(0, 99)],
                    variant_ids[random_int(0, 99)],
                    quantity,
                    unit_price,
                    discount,
                    sub_total);
        else
            fprintf(filePointer, "('%s', '%s', '%s', '%d', '%.2f', '%.2f', '%.2f');\n\n",
                    orderdetail_ids[i],
                    order_ids[random_int(0, 99)],
                    variant_ids[random_int(0, 99)],
                    quantity,
                    unit_price,
                    discount,
                    sub_total);
    }

    // Insert bảng feedback
    fprintf(filePointer, "INSERT INTO feedback(feedback_id, orderdetail_id, feedback, rating, feedback_date) VALUES\n");
    for (int i = 0; i < 150; i++)
    {
        gen_feedback_id(i);
        if (i != 149)
            fprintf(filePointer, "('%s', '%s', '%s', '%d', '2023-%02d-%02d'),\n",
                    feedback_ids[i],
                    orderdetail_ids[random_int(0, 199)],
                    feedback_content[random_int(0, 19)],
                    random_int(1, 5),
                    random_int(1, 12),
                    random_int(1, 28));
        else
            fprintf(filePointer, "('%s', '%s', '%s', '%d', '2023-%02d-%02d');\n\n",
                    feedback_ids[i],
                    orderdetail_ids[random_int(0, 199)],
                    feedback_content[random_int(0, 19)],
                    random_int(1, 5),
                    random_int(1, 12),
                    random_int(1, 28));
    }
    // Đóng file sau khi hoàn thành việc ghi.
    // Điều này rất quan trọng để đảm bảo tất cả dữ liệu được lưu vào file và giải phóng tài nguyên.
    fclose(filePointer);

    printf("Ghi du lieu thanh cong vao shoestore.sql\n");

    return 0; // Trả về 0 nếu chương trình chạy thành công
}