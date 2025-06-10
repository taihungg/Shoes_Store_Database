#include <stdio.h>  // Thư viện chuẩn cho các hàm nhập/xuất
#include <stdlib.h> // Cho rand() và srand()
#include <time.h>   // Cho time()
#include <string.h> // Cần thiết cho hàm strcpy

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

    // 1. Danh sách các đầu số di động hợp lệ của Việt Nam
    const char *dau_so[] = {"090", "091", "098", "086", "077", "059", "035", "038"};
    int so_luong_dau_so = sizeof(dau_so) / sizeof(dau_so[0]);

    // 2. Chọn ngẫu nhiên một đầu số
    const char *dau_so_duoc_chon = dau_so[rand() % so_luong_dau_so];

    // 3. Sao chép đầu số đã chọn vào buffer
    strcpy(sdt_buffer, dau_so_duoc_chon);

    // 4. Tạo 7 chữ số còn lại (vì đầu số đã có 3 chữ số)
    for (int i = 3; i < 10; i++)
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
    static char user_buffer[11]; // Tối đa 10 ký tự + '\0'
    const char *charset = "abcdefghijklmnopqrstuvwxyz0123456789";
    int charset_len = strlen(charset);

    int len = (rand() % 5) + 6; // Độ dài từ 6 đến 10
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
    static char email_buffer[31]; // Tối đa 30 ký tự + '\0'
    const char *charset = "abcdefghijklmnopqrstuvwxyz0123456789";
    const char *domain = "@gmail.com";
    int charset_len = strlen(charset);

    // Tự tạo phần username riêng, không gọi hàm tao_username_static()
    int username_len = (rand() % 5) + 6; // Độ dài từ 6 đến 10
    for (int i = 0; i < username_len; i++)
    {
        email_buffer[i] = charset[rand() % charset_len];
    }

    // Nối đuôi domain vào
    strcpy(&email_buffer[username_len], domain);

    return email_buffer;
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

    for (int i = 0; i < 100; i++)
    {
        // cuối dòng là dấu ,
        if (i != 99)
            fprintf(filePointer, "('%d', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s'),\n" /*dấu , cuối dòng*/,
                    i + 1, first_name[random_int(0, 199)], last_name[random_int(0, 199)],
                    address[random_int(0, 199)], city[random_int(0, 199)], district[random_int(0, 199)],
                    gen_phone_number(), gen_email(), credit_card[random_int(0, 199)],
                    dob[random_int(0, 199)], gender[random_int(0, 1)], gen_username(), gen_password());

        // cuối dòng là dấu;
        else
            fprintf(filePointer, "('%d', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s');\n" /*dấu ; cuối dòng*/,
                    i + 1, first_name[random_int(0, 199)], last_name[random_int(0, 199)],
                    address[random_int(0, 199)], city[random_int(0, 199)], district[random_int(0, 199)],
                    gen_phone_number(), gen_email(), credit_card[random_int(0, 199)],
                    dob[random_int(0, 199)], gender[random_int(0, 1)], gen_username(), gen_password());
    }

    // Tạo dữ liệu cho bảng employee
    fprintf(filePointer, "\n-- Insert employees\nINSERT INTO employee (employee_id, first_name, last_name, dob, phone_number, email, username, password) VALUES\n");

    for (int i = 0; i < 50; i++)
    {
        if (i != 49)
        {
            fprintf(filePointer, "('%d', '%s', '%s', '%s', '%s', '%s', '%s', '%s'),\n",
                    i + 1,
                    first_name[random_int(0, 199)],
                    last_name[random_int(0, 199)],
                    dob[random_int(0, 199)],
                    gen_phone_number(),
                    gen_email(),
                    gen_username(),
                    gen_password());
        }
        else
        {
            fprintf(filePointer, "('%d', '%s', '%s', '%s', '%s', '%s', '%s', '%s');\n",
                    i + 1,
                    first_name[random_int(0, 199)],
                    last_name[random_int(0, 199)],
                    dob[random_int(0, 199)],
                    gen_phone_number(),
                    gen_email(),
                    gen_username(),
                    gen_password());
        }
    }

    // Đóng file sau khi hoàn thành việc ghi.
    // Điều này rất quan trọng để đảm bảo tất cả dữ liệu được lưu vào file và giải phóng tài nguyên.
    fclose(filePointer);

    printf("Ghi du lieu thanh cong vao shoestore.sql\n");

    return 0; // Trả về 0 nếu chương trình chạy thành công
}