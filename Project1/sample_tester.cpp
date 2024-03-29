#include <cstdlib>
#include <cstdio>
#include <chrono>
#include <thread>
#include "sample_tester.h"

using namespace std;

//=================================================================================================
void CCustomerTest::Add(const std::string &destination,
                        const CCargo &cargo) {
    m_Data[destination].push_back(cargo);
}

//-------------------------------------------------------------------------------------------------
void CCustomerTest::Quote(const std::string &destination, std::vector<CCargo> &cargo) {
    if (auto it = m_Data.find(destination); it != m_Data.end())
        cargo = it->second;
    else
        cargo.clear();
}

//=================================================================================================
CShipTest::CShipTest(std::string destination,
                     int maxWeight,
                     int maxVolume,
                     int expected)
        : CShip(move(destination), maxWeight, maxVolume),
          m_Expected(expected) {
}

//-------------------------------------------------------------------------------------------------
void CShipTest::Load(const std::vector<CCargo> &cargo) {
    m_Load = cargo;
}

//-------------------------------------------------------------------------------------------------
bool CShipTest::Validate(void) const {
    int sum = 0;
    for (auto x : m_Load)
        sum += x.m_Fee;
    return sum == m_Expected;
}

//=================================================================================================
AShipTest CSampleData::PrepareTest(std::string destination,
                                   std::vector<ACustomerTest> customers) const {
    for (auto x : m_Cargo)
        customers[rand() % customers.size()]->Add(destination, x);
    return make_shared<CShipTest>(move(destination), m_MaxWeight, m_MaxVolume, m_Expected);
}

//=================================================================================================
std::vector<CSampleData> g_TestExtra =
        {
                // 20
                {8397,  335, 233, {CCargo(894, 24, 37),  CCargo(398, 31, 13),  CCargo(423, 15, 29),  CCargo(774, 33,
                                                                                                            26), CCargo(
                        626, 49, 13),  CCargo(903, 24, 35),  CCargo(609, 20, 31),  CCargo(382, 45, 8),   CCargo(868, 25,
                                                                                                                32), CCargo(
                        331, 12, 30),  CCargo(218, 41, 5),   CCargo(591, 19, 34),  CCargo(2029, 41, 48), CCargo(328, 11,
                                                                                                                32), CCargo(
                        345, 11, 32),  CCargo(176, 32, 6),   CCargo(677, 26, 25),  CCargo(985, 46, 20),  CCargo(1623,
                                                                                                                37,
                                                                                                                44), CCargo(
                        181, 33, 6)}},
                {8142,  383, 232, {CCargo(187, 43, 4),   CCargo(323, 36, 9),   CCargo(214, 5, 43),   CCargo(1196, 28,
                                                                                                            46), CCargo(
                        1209, 26, 45), CCargo(807, 18, 46),  CCargo(1421, 46, 32), CCargo(750, 36, 21),  CCargo(598, 23,
                                                                                                                24), CCargo(
                        1248, 46, 27), CCargo(574, 27, 21),  CCargo(183, 25, 7),   CCargo(490, 48, 10),  CCargo(894, 24,
                                                                                                                37), CCargo(
                        398, 31, 13),  CCargo(423, 15, 29),  CCargo(774, 33, 26),  CCargo(626, 49, 13),  CCargo(903, 24,
                                                                                                                35), CCargo(
                        609, 20, 31),  CCargo(382, 45, 8)}},
                {10052, 291, 278, {CCargo(15, 4, 4),     CCargo(138, 6, 23),   CCargo(214, 11, 18),  CCargo(648, 16,
                                                                                                            44), CCargo(
                        141, 8, 18),   CCargo(258, 34, 7),   CCargo(1487, 36, 41), CCargo(1115, 38, 31), CCargo(106, 33,
                                                                                                                3),  CCargo(
                        247, 11, 23),  CCargo(941, 38, 25),  CCargo(62, 2, 29),    CCargo(939, 26, 38),  CCargo(97, 21,
                                                                                                                5),  CCargo(
                        295, 27, 11),  CCargo(2058, 46, 44), CCargo(1268, 43, 30), CCargo(362, 21, 19),  CCargo(90, 33,
                                                                                                                3),  CCargo(
                        325, 27, 12),  CCargo(2030, 46, 49), CCargo(996, 20, 49)}},
                {12928, 365, 364, {CCargo(2058, 46, 44), CCargo(1268, 43, 30), CCargo(362, 21, 19),  CCargo(90, 33,
                                                                                                            3),  CCargo(
                        325, 27, 12),  CCargo(2030, 46, 49), CCargo(996, 20, 49),  CCargo(403, 16, 26),  CCargo(1239,
                                                                                                                28,
                                                                                                                45), CCargo(
                        787, 35, 22),  CCargo(189, 10, 19),  CCargo(452, 38, 13),  CCargo(326, 10, 33),  CCargo(190, 12,
                                                                                                                16), CCargo(
                        698, 16, 42),  CCargo(1658, 41, 39), CCargo(391, 42, 9),   CCargo(494, 22, 24),  CCargo(71, 39,
                                                                                                                2),  CCargo(
                        398, 11, 36),  CCargo(1946, 41, 44), CCargo(489, 16, 33),  CCargo(868, 20, 41)}},
                {10020, 310, 285, {CCargo(43, 22, 2),    CCargo(737, 15, 46),  CCargo(547, 14, 43),  CCargo(673, 31,
                                                                                                            24), CCargo(
                        254, 28, 9),   CCargo(264, 7, 36),   CCargo(184, 6, 32),   CCargo(1476, 42, 38), CCargo(149, 6,
                                                                                                                25), CCargo(
                        447, 42, 10),  CCargo(607, 19, 30),  CCargo(1807, 40, 43), CCargo(269, 33, 8),   CCargo(1184,
                                                                                                                35,
                                                                                                                37), CCargo(
                        544, 36, 16),  CCargo(360, 15, 22),  CCargo(79, 3, 26),    CCargo(313, 17, 19),  CCargo(564, 23,
                                                                                                                23), CCargo(
                        678, 47, 16),  CCargo(1312, 39, 33), CCargo(739, 31, 24),  CCargo(135, 19, 7),   CCargo(1905,
                                                                                                                49,
                                                                                                                40)}},
                // 25
                {10679, 361, 267, {CCargo(1252, 38, 31), CCargo(188, 26, 8),   CCargo(1254, 42, 28), CCargo(806, 39,
                                                                                                            19), CCargo(
                        679, 20, 33),  CCargo(706, 33, 20),  CCargo(119, 30, 4),   CCargo(16, 8, 2),     CCargo(1559,
                                                                                                                40,
                                                                                                                36), CCargo(
                        208, 6, 36),   CCargo(353, 13, 25),  CCargo(7, 4, 2),      CCargo(258, 6, 42),   CCargo(1649,
                                                                                                                47,
                                                                                                                32), CCargo(
                        135, 44, 3),   CCargo(833, 27, 34),  CCargo(257, 20, 14),  CCargo(851, 44, 21),  CCargo(316, 27,
                                                                                                                11), CCargo(
                        371, 23, 16),  CCargo(956, 39, 27),  CCargo(980, 36, 30),  CCargo(1472, 39, 35), CCargo(676, 21,
                                                                                                                32), CCargo(
                        573, 21, 27)}},
                {11059, 399, 357, {CCargo(38, 6, 7),     CCargo(1531, 41, 41), CCargo(385, 35, 11),  CCargo(122, 3,
                                                                                                            39), CCargo(
                        447, 21, 23),  CCargo(769, 24, 33),  CCargo(876, 22, 37),  CCargo(156, 3, 49),   CCargo(73, 24,
                                                                                                                3),  CCargo(
                        495, 48, 10),  CCargo(590, 40, 14),  CCargo(213, 42, 5),   CCargo(1810, 45, 38), CCargo(852, 21,
                                                                                                                40), CCargo(
                        86, 8, 12),    CCargo(491, 14, 34),  CCargo(213, 31, 7),   CCargo(229, 26, 9),   CCargo(520, 17,
                                                                                                                31), CCargo(
                        1331, 45, 29), CCargo(621, 29, 20),  CCargo(254, 18, 13),  CCargo(382, 46, 8),   CCargo(1038,
                                                                                                                37,
                                                                                                                28), CCargo(
                        567, 16, 34),  CCargo(812, 18, 46)}},
                {12660, 367, 362, {CCargo(319, 12, 26),  CCargo(167, 14, 11),  CCargo(543, 48, 11),  CCargo(687, 24,
                                                                                                            27), CCargo(
                        2255, 47, 47), CCargo(777, 49, 16),  CCargo(396, 30, 13),  CCargo(178, 4, 47),   CCargo(202, 8,
                                                                                                                24), CCargo(
                        813, 38, 21),  CCargo(1386, 47, 32), CCargo(1224, 29, 44), CCargo(1118, 26, 43), CCargo(154, 10,
                                                                                                                17), CCargo(
                        789, 48, 15),  CCargo(429, 30, 15),  CCargo(176, 4, 44),   CCargo(1493, 32, 47), CCargo(286, 44,
                                                                                                                6),  CCargo(
                        1338, 33, 42), CCargo(610, 14, 40),  CCargo(385, 19, 19),  CCargo(1557, 34, 44), CCargo(36, 10,
                                                                                                                4),  CCargo(
                        34, 12, 3),    CCargo(347, 11, 31),  CCargo(812, 24, 34)}},
                {13013, 394, 411, {CCargo(1819, 40, 42), CCargo(1053, 37, 30), CCargo(872, 25, 34),  CCargo(841, 38,
                                                                                                            23), CCargo(
                        623, 41, 16),  CCargo(1273, 37, 38), CCargo(396, 40, 11),  CCargo(108, 24, 5),   CCargo(1090,
                                                                                                                36,
                                                                                                                33), CCargo(
                        559, 17, 31),  CCargo(974, 45, 21),  CCargo(310, 41, 8),   CCargo(168, 5, 31),   CCargo(647, 35,
                                                                                                                19), CCargo(
                        22, 2, 11),    CCargo(695, 15, 47),  CCargo(607, 16, 37),  CCargo(199, 16, 12),  CCargo(820, 18,
                                                                                                                47), CCargo(
                        336, 22, 14),  CCargo(113, 13, 9),   CCargo(2151, 44, 49), CCargo(29, 8, 4),     CCargo(147, 4,
                                                                                                                37), CCargo(
                        866, 22, 38),  CCargo(18, 6, 3),     CCargo(472, 27, 18),  CCargo(335, 10, 33)}},
                {11206, 421, 357, {CCargo(1670, 39, 46), CCargo(496, 31, 15),  CCargo(223, 35, 6),   CCargo(267, 18,
                                                                                                            15), CCargo(
                        618, 27, 25),  CCargo(307, 47, 7),   CCargo(98, 3, 32),    CCargo(967, 38, 28),  CCargo(538, 31,
                                                                                                                16), CCargo(
                        260, 6, 48),   CCargo(443, 11, 37),  CCargo(323, 18, 19),  CCargo(53, 11, 5),    CCargo(42, 2,
                                                                                                                21), CCargo(
                        1037, 24, 47), CCargo(1163, 28, 44), CCargo(1773, 36, 46), CCargo(668, 20, 34),  CCargo(367, 22,
                                                                                                                16), CCargo(
                        394, 19, 20),  CCargo(571, 20, 29),  CCargo(876, 18, 46),  CCargo(210, 28, 7),   CCargo(336, 44,
                                                                                                                8),  CCargo(
                        708, 25, 30),  CCargo(220, 30, 8),   CCargo(1593, 41, 43), CCargo(459, 34, 13),  CCargo(223, 6,
                                                                                                                34)}},
                // 30
                {11502, 338, 317, {CCargo(177, 6, 27),   CCargo(1323, 45, 30), CCargo(1176, 37, 34), CCargo(718, 23,
                                                                                                            31), CCargo(
                        1316, 40, 30), CCargo(803, 24, 36),  CCargo(1582, 40, 42), CCargo(190, 35, 6),   CCargo(76, 39,
                                                                                                                2),  CCargo(
                        20, 5, 4),     CCargo(58, 7, 9),     CCargo(31, 6, 5),     CCargo(987, 25, 40),  CCargo(420, 33,
                                                                                                                14), CCargo(
                        56, 11, 5),    CCargo(288, 11, 27),  CCargo(287, 18, 17),  CCargo(55, 29, 2),    CCargo(1154,
                                                                                                                30,
                                                                                                                40), CCargo(
                        2099, 49, 44), CCargo(1529, 31, 49), CCargo(204, 40, 5),   CCargo(798, 29, 28),  CCargo(24, 2,
                                                                                                                12), CCargo(
                        92, 4, 22),    CCargo(1070, 35, 32), CCargo(250, 5, 49),   CCargo(401, 14, 28),  CCargo(228, 29,
                                                                                                                8),  CCargo(
                        295, 44, 7)}},
                {15012, 424, 359, {CCargo(841, 27, 33),  CCargo(69, 9, 8),     CCargo(433, 42, 10),  CCargo(2151, 41,
                                                                                                            48), CCargo(
                        1327, 37, 37), CCargo(280, 38, 8),   CCargo(269, 23, 12),  CCargo(1571, 41, 39), CCargo(803, 49,
                                                                                                                15), CCargo(
                        1179, 31, 35), CCargo(475, 39, 12),  CCargo(39, 2, 19),    CCargo(245, 19, 12),  CCargo(9, 3,
                                                                                                                3),  CCargo(
                        1943, 49, 39), CCargo(507, 18, 27),  CCargo(1280, 24, 49), CCargo(1758, 42, 40), CCargo(506, 14,
                                                                                                                40), CCargo(
                        262, 12, 21),  CCargo(97, 9, 10),    CCargo(365, 38, 10),  CCargo(675, 24, 28),  CCargo(557, 19,
                                                                                                                29), CCargo(
                        325, 12, 28),  CCargo(1935, 40, 45), CCargo(549, 27, 19),  CCargo(272, 24, 11),  CCargo(285, 12,
                                                                                                                24), CCargo(
                        488, 13, 35),  CCargo(1796, 47, 42)}},
                {10871, 316, 418, {CCargo(1512, 44, 36), CCargo(374, 36, 11),  CCargo(1033, 33, 30), CCargo(725, 29,
                                                                                                            27), CCargo(
                        600, 25, 23),  CCargo(906, 26, 38),  CCargo(562, 17, 33),  CCargo(84, 9, 9),     CCargo(211, 13,
                                                                                                                16), CCargo(
                        251, 17, 14),  CCargo(161, 18, 9),   CCargo(1382, 31, 43), CCargo(1046, 42, 26), CCargo(149, 28,
                                                                                                                5),  CCargo(
                        967, 35, 29),  CCargo(95, 21, 5),    CCargo(566, 26, 21),  CCargo(61, 2, 29),    CCargo(1369,
                                                                                                                36,
                                                                                                                41), CCargo(
                        133, 17, 8),   CCargo(145, 6, 24),   CCargo(177, 30, 6),   CCargo(752, 15, 46),  CCargo(657, 29,
                                                                                                                25), CCargo(
                        204, 20, 10),  CCargo(1027, 33, 30), CCargo(193, 35, 6),   CCargo(145, 20, 7),   CCargo(504, 12,
                                                                                                                42), CCargo(
                        175, 19, 9),   CCargo(468, 39, 13),  CCargo(694, 18, 41)}},
                {16383, 380, 509, {CCargo(2166, 44, 49), CCargo(288, 13, 21),  CCargo(396, 11, 33),  CCargo(821, 28,
                                                                                                            27), CCargo(
                        149, 4, 34),   CCargo(338, 9, 36),   CCargo(256, 32, 8),   CCargo(222, 17, 13),  CCargo(1974,
                                                                                                                47,
                                                                                                                39), CCargo(
                        805, 17, 47),  CCargo(1854, 45, 41), CCargo(95, 22, 4),    CCargo(170, 12, 14),  CCargo(369, 10,
                                                                                                                40), CCargo(
                        311, 7, 42),   CCargo(12, 6, 2),     CCargo(1352, 41, 32), CCargo(880, 17, 48),  CCargo(2000,
                                                                                                                43,
                                                                                                                45), CCargo(
                        466, 38, 12),  CCargo(110, 16, 7),   CCargo(1146, 41, 28), CCargo(1514, 38, 38), CCargo(901, 19,
                                                                                                                47), CCargo(
                        94, 24, 4),    CCargo(123, 14, 9),   CCargo(1701, 39, 48), CCargo(331, 23, 16),  CCargo(194, 18,
                                                                                                                10), CCargo(
                        87, 2, 47),    CCargo(396, 32, 13),  CCargo(26, 5, 5),     CCargo(1236, 29, 42)}},
                {13210, 384, 411, {CCargo(1674, 43, 41), CCargo(368, 37, 10),  CCargo(244, 34, 7),   CCargo(786, 20,
                                                                                                            42), CCargo(
                        424, 44, 9),   CCargo(819, 31, 25),  CCargo(48, 2, 25),    CCargo(1215, 27, 46), CCargo(440, 11,
                                                                                                                38), CCargo(
                        45, 25, 2),    CCargo(849, 18, 44),  CCargo(870, 30, 32),  CCargo(89, 6, 16),    CCargo(1343,
                                                                                                                36,
                                                                                                                34), CCargo(
                        1213, 45, 29), CCargo(390, 38, 10),  CCargo(285, 28, 11),  CCargo(1483, 44, 37), CCargo(748, 15,
                                                                                                                47), CCargo(
                        93, 4, 22),    CCargo(198, 5, 38),   CCargo(866, 47, 19),  CCargo(1137, 48, 23), CCargo(60, 7,
                                                                                                                9),  CCargo(
                        30, 7, 4),     CCargo(526, 14, 41),  CCargo(819, 45, 19),  CCargo(50, 4, 14),    CCargo(177, 6,
                                                                                                                27), CCargo(
                        1323, 45, 30), CCargo(1176, 37, 34), CCargo(718, 23, 31),  CCargo(1316, 40, 30), CCargo(803, 24,
                                                                                                                36)}},
                // 35
                {18887, 487, 526, {CCargo(938, 21, 48),  CCargo(841, 27, 33),  CCargo(69, 9, 8),     CCargo(433, 42,
                                                                                                            10), CCargo(
                        2151, 41, 48), CCargo(1327, 37, 37), CCargo(280, 38, 8),   CCargo(269, 23, 12),  CCargo(1571,
                                                                                                                41,
                                                                                                                39), CCargo(
                        803, 49, 15),  CCargo(1179, 31, 35), CCargo(475, 39, 12),  CCargo(39, 2, 19),    CCargo(245, 19,
                                                                                                                12), CCargo(
                        9, 3, 3),      CCargo(1943, 49, 39), CCargo(507, 18, 27),  CCargo(1280, 24, 49), CCargo(1758,
                                                                                                                42,
                                                                                                                40), CCargo(
                        506, 14, 40),  CCargo(262, 12, 21),  CCargo(97, 9, 10),    CCargo(365, 38, 10),  CCargo(675, 24,
                                                                                                                28), CCargo(
                        557, 19, 29),  CCargo(325, 12, 28),  CCargo(1935, 40, 45), CCargo(549, 27, 19),  CCargo(272, 24,
                                                                                                                11), CCargo(
                        285, 12, 24),  CCargo(488, 13, 35),  CCargo(1796, 47, 42), CCargo(1278, 45, 30), CCargo(63, 12,
                                                                                                                5),  CCargo(
                        824, 37, 23)}},
                {16217, 403, 523, {CCargo(1566, 34, 47), CCargo(384, 29, 14),  CCargo(84, 6, 15),    CCargo(1723, 38,
                                                                                                            48), CCargo(
                        1246, 36, 37), CCargo(1808, 43, 41), CCargo(79, 14, 6),    CCargo(637, 25, 28),  CCargo(170, 11,
                                                                                                                15), CCargo(
                        42, 2, 23),    CCargo(221, 35, 7),   CCargo(200, 6, 35),   CCargo(711, 18, 39),  CCargo(706, 26,
                                                                                                                27), CCargo(
                        459, 37, 13),  CCargo(297, 46, 7),   CCargo(499, 28, 19),  CCargo(1804, 40, 43), CCargo(151, 42,
                                                                                                                4),  CCargo(
                        129, 26, 5),   CCargo(1160, 30, 38), CCargo(1315, 32, 43), CCargo(461, 46, 11),  CCargo(916, 25,
                                                                                                                36), CCargo(
                        73, 3, 23),    CCargo(348, 16, 20),  CCargo(972, 22, 46),  CCargo(1070, 31, 37), CCargo(538, 19,
                                                                                                                30), CCargo(
                        115, 20, 6),   CCargo(1375, 43, 35), CCargo(424, 23, 17),  CCargo(444, 37, 13),  CCargo(1579,
                                                                                                                40,
                                                                                                                37), CCargo(
                        728, 20, 38),  CCargo(61, 12, 5)}},
                {13979, 528, 447, {CCargo(468, 39, 13),  CCargo(694, 18, 41),  CCargo(246, 38, 7),   CCargo(1253, 36,
                                                                                                            34), CCargo(
                        201, 38, 5),   CCargo(669, 19, 36),  CCargo(109, 5, 22),   CCargo(408, 10, 40),  CCargo(83, 42,
                                                                                                                2),  CCargo(
                        388, 19, 20),  CCargo(471, 49, 9),   CCargo(181, 7, 25),   CCargo(251, 17, 14),  CCargo(1165,
                                                                                                                24,
                                                                                                                49), CCargo(
                        222, 6, 37),   CCargo(292, 44, 7),   CCargo(154, 15, 10),  CCargo(697, 39, 18),  CCargo(230, 21,
                                                                                                                11), CCargo(
                        1291, 43, 28), CCargo(606, 24, 28),  CCargo(578, 17, 34),  CCargo(4, 2, 2),      CCargo(1007,
                                                                                                                40,
                                                                                                                24), CCargo(
                        390, 14, 28),  CCargo(914, 39, 23),  CCargo(117, 3, 37),   CCargo(874, 35, 27),  CCargo(399, 9,
                                                                                                                46), CCargo(
                        1421, 33, 40), CCargo(359, 26, 14),  CCargo(747, 27, 30),  CCargo(83, 3, 30),    CCargo(854, 40,
                                                                                                                21), CCargo(
                        857, 28, 33),  CCargo(89, 4, 22),    CCargo(765, 33, 24)}},
                {18727, 543, 495, {CCargo(1685, 38, 44), CCargo(364, 10, 34),  CCargo(308, 13, 23),  CCargo(536, 12,
                                                                                                            47), CCargo(
                        1727, 45, 35), CCargo(1482, 36, 39), CCargo(461, 23, 19),  CCargo(878, 31, 28),  CCargo(289, 23,
                                                                                                                13), CCargo(
                        476, 26, 19),  CCargo(347, 46, 8),   CCargo(414, 24, 16),  CCargo(445, 17, 27),  CCargo(1783,
                                                                                                                49,
                                                                                                                38), CCargo(
                        484, 13, 34),  CCargo(274, 13, 20),  CCargo(75, 2, 41),    CCargo(910, 40, 22),  CCargo(905, 19,
                                                                                                                44), CCargo(
                        722, 36, 21),  CCargo(50, 3, 17),    CCargo(541, 13, 40),  CCargo(59, 9, 7),     CCargo(157, 25,
                                                                                                                7),  CCargo(
                        787, 40, 19),  CCargo(1068, 39, 30), CCargo(935, 28, 31),  CCargo(689, 34, 21),  CCargo(661, 18,
                                                                                                                39), CCargo(
                        357, 14, 25),  CCargo(792, 28, 26),  CCargo(1911, 48, 38), CCargo(1641, 34, 45), CCargo(1058,
                                                                                                                46,
                                                                                                                21), CCargo(
                        489, 46, 11),  CCargo(1620, 31, 48), CCargo(929, 34, 27),  CCargo(349, 29, 11)}},
                {14760, 566, 400, {CCargo(30, 7, 4),     CCargo(526, 14, 41),  CCargo(819, 45, 19),  CCargo(50, 4,
                                                                                                            14), CCargo(
                        177, 6, 27),   CCargo(1323, 45, 30), CCargo(1176, 37, 34), CCargo(718, 23, 31),  CCargo(1316,
                                                                                                                40,
                                                                                                                30), CCargo(
                        803, 24, 36),  CCargo(1582, 40, 42), CCargo(190, 35, 6),   CCargo(76, 39, 2),    CCargo(20, 5,
                                                                                                                4),  CCargo(
                        58, 7, 9),     CCargo(31, 6, 5),     CCargo(987, 25, 40),  CCargo(420, 33, 14),  CCargo(56, 11,
                                                                                                                5),  CCargo(
                        288, 11, 27),  CCargo(287, 18, 17),  CCargo(55, 29, 2),    CCargo(1154, 30, 40), CCargo(2099,
                                                                                                                49,
                                                                                                                44), CCargo(
                        1529, 31, 49), CCargo(204, 40, 5),   CCargo(798, 29, 28),  CCargo(24, 2, 12),    CCargo(92, 4,
                                                                                                                22), CCargo(
                        1070, 35, 32), CCargo(250, 5, 49),   CCargo(401, 14, 28),  CCargo(228, 29, 8),   CCargo(295, 44,
                                                                                                                7),  CCargo(
                        495, 14, 37),  CCargo(1048, 40, 27), CCargo(136, 21, 6),   CCargo(266, 41, 7),   CCargo(228, 25,
                                                                                                                9)}},
                // 40
                {19072, 477, 620, {CCargo(261, 6, 47),   CCargo(625, 32, 20),  CCargo(1077, 28, 38), CCargo(1171, 36,
                                                                                                            35), CCargo(
                        131, 9, 15),   CCargo(412, 19, 22),  CCargo(143, 4, 37),   CCargo(542, 29, 20),  CCargo(524, 46,
                                                                                                                11), CCargo(
                        140, 15, 10),  CCargo(413, 32, 14),  CCargo(1753, 39, 45), CCargo(218, 10, 23),  CCargo(402, 37,
                                                                                                                10), CCargo(
                        724, 45, 17),  CCargo(507, 14, 35),  CCargo(1274, 35, 37), CCargo(50, 3, 16),    CCargo(129, 12,
                                                                                                                12), CCargo(
                        1096, 45, 26), CCargo(44, 5, 9),     CCargo(502, 11, 47),  CCargo(259, 35, 7),   CCargo(2212,
                                                                                                                47,
                                                                                                                43), CCargo(
                        1605, 44, 38), CCargo(17, 8, 2),     CCargo(1506, 40, 36), CCargo(448, 13, 38),  CCargo(139, 3,
                                                                                                                49), CCargo(
                        139, 3, 44),   CCargo(624, 12, 48),  CCargo(327, 34, 9),   CCargo(137, 3, 42),   CCargo(1794,
                                                                                                                42,
                                                                                                                40), CCargo(
                        1421, 41, 34), CCargo(286, 7, 40),   CCargo(210, 7, 31),   CCargo(1622, 42, 42), CCargo(1773,
                                                                                                                44,
                                                                                                                44), CCargo(
                        452, 9, 46)}},
                {15692, 515, 458, {CCargo(568, 17, 37),  CCargo(76, 9, 8),     CCargo(468, 23, 19),  CCargo(183, 7,
                                                                                                            27), CCargo(
                        71, 36, 2),    CCargo(144, 4, 33),   CCargo(1412, 49, 27), CCargo(71, 2, 35),    CCargo(1788,
                                                                                                                36,
                                                                                                                47), CCargo(
                        317, 38, 8),   CCargo(91, 4, 23),    CCargo(158, 5, 31),   CCargo(187, 43, 4),   CCargo(323, 36,
                                                                                                                9),  CCargo(
                        214, 5, 43),   CCargo(1196, 28, 46), CCargo(1209, 26, 45), CCargo(807, 18, 46),  CCargo(1421,
                                                                                                                46,
                                                                                                                32), CCargo(
                        750, 36, 21),  CCargo(598, 23, 24),  CCargo(1248, 46, 27), CCargo(574, 27, 21),  CCargo(183, 25,
                                                                                                                7),  CCargo(
                        490, 48, 10),  CCargo(894, 24, 37),  CCargo(398, 31, 13),  CCargo(423, 15, 29),  CCargo(774, 33,
                                                                                                                26), CCargo(
                        626, 49, 13),  CCargo(903, 24, 35),  CCargo(609, 20, 31),  CCargo(382, 45, 8),   CCargo(868, 25,
                                                                                                                32), CCargo(
                        331, 12, 30),  CCargo(218, 41, 5),   CCargo(591, 19, 34),  CCargo(2029, 41, 48), CCargo(328, 11,
                                                                                                                32), CCargo(
                        345, 11, 32),  CCargo(176, 32, 6)}},
                {15196, 502, 422, {CCargo(60, 7, 9),     CCargo(30, 7, 4),     CCargo(526, 14, 41),  CCargo(819, 45,
                                                                                                            19), CCargo(
                        50, 4, 14),    CCargo(177, 6, 27),   CCargo(1323, 45, 30), CCargo(1176, 37, 34), CCargo(718, 23,
                                                                                                                31), CCargo(
                        1316, 40, 30), CCargo(803, 24, 36),  CCargo(1582, 40, 42), CCargo(190, 35, 6),   CCargo(76, 39,
                                                                                                                2),  CCargo(
                        20, 5, 4),     CCargo(58, 7, 9),     CCargo(31, 6, 5),     CCargo(987, 25, 40),  CCargo(420, 33,
                                                                                                                14), CCargo(
                        56, 11, 5),    CCargo(288, 11, 27),  CCargo(287, 18, 17),  CCargo(55, 29, 2),    CCargo(1154,
                                                                                                                30,
                                                                                                                40), CCargo(
                        2099, 49, 44), CCargo(1529, 31, 49), CCargo(204, 40, 5),   CCargo(798, 29, 28),  CCargo(24, 2,
                                                                                                                12), CCargo(
                        92, 4, 22),    CCargo(1070, 35, 32), CCargo(250, 5, 49),   CCargo(401, 14, 28),  CCargo(228, 29,
                                                                                                                8),  CCargo(
                        295, 44, 7),   CCargo(495, 14, 37),  CCargo(1048, 40, 27), CCargo(136, 21, 6),   CCargo(266, 41,
                                                                                                                7),  CCargo(
                        228, 25, 9),   CCargo(567, 14, 43),  CCargo(1164, 27, 46)}},
                {15936, 474, 556, {CCargo(590, 13, 46),  CCargo(113, 3, 38),   CCargo(51, 8, 6),     CCargo(38, 6,
                                                                                                            7),  CCargo(
                        1531, 41, 41), CCargo(385, 35, 11),  CCargo(122, 3, 39),   CCargo(447, 21, 23),  CCargo(769, 24,
                                                                                                                33), CCargo(
                        876, 22, 37),  CCargo(156, 3, 49),   CCargo(73, 24, 3),    CCargo(495, 48, 10),  CCargo(590, 40,
                                                                                                                14), CCargo(
                        213, 42, 5),   CCargo(1810, 45, 38), CCargo(852, 21, 40),  CCargo(86, 8, 12),    CCargo(491, 14,
                                                                                                                34), CCargo(
                        213, 31, 7),   CCargo(229, 26, 9),   CCargo(520, 17, 31),  CCargo(1331, 45, 29), CCargo(621, 29,
                                                                                                                20), CCargo(
                        254, 18, 13),  CCargo(382, 46, 8),   CCargo(1038, 37, 28), CCargo(567, 16, 34),  CCargo(812, 18,
                                                                                                                46), CCargo(
                        56, 2, 28),    CCargo(90, 22, 4),    CCargo(744, 41, 19),  CCargo(210, 14, 14),  CCargo(1674,
                                                                                                                43,
                                                                                                                41), CCargo(
                        368, 37, 10),  CCargo(244, 34, 7),   CCargo(786, 20, 42),  CCargo(424, 44, 9),   CCargo(819, 31,
                                                                                                                25), CCargo(
                        48, 2, 25),    CCargo(1215, 27, 46), CCargo(440, 11, 38),  CCargo(45, 25, 2)}},
                {22735, 597, 662, {CCargo(323, 18, 19),  CCargo(53, 11, 5),    CCargo(42, 2, 21),    CCargo(1037, 24,
                                                                                                            47), CCargo(
                        1163, 28, 44), CCargo(1773, 36, 46), CCargo(668, 20, 34),  CCargo(367, 22, 16),  CCargo(394, 19,
                                                                                                                20), CCargo(
                        571, 20, 29),  CCargo(876, 18, 46),  CCargo(210, 28, 7),   CCargo(336, 44, 8),   CCargo(708, 25,
                                                                                                                30), CCargo(
                        220, 30, 8),   CCargo(1593, 41, 43), CCargo(459, 34, 13),  CCargo(223, 6, 34),   CCargo(120, 41,
                                                                                                                3),  CCargo(
                        625, 26, 22),  CCargo(1886, 46, 38), CCargo(567, 37, 17),  CCargo(334, 30, 12),  CCargo(1577,
                                                                                                                43,
                                                                                                                35), CCargo(
                        103, 6, 16),   CCargo(92, 11, 8),    CCargo(432, 12, 40),  CCargo(2144, 46, 45), CCargo(1691,
                                                                                                                45,
                                                                                                                36), CCargo(
                        193, 16, 13),  CCargo(151, 14, 10),  CCargo(383, 9, 45),   CCargo(257, 10, 26),  CCargo(300, 17,
                                                                                                                19), CCargo(
                        119, 5, 24),   CCargo(1577, 47, 33), CCargo(1506, 35, 44), CCargo(1344, 35, 40), CCargo(633, 20,
                                                                                                                35), CCargo(
                        13, 7, 2),     CCargo(193, 14, 14),  CCargo(212, 10, 22),  CCargo(693, 21, 31),  CCargo(1861,
                                                                                                                43,
                                                                                                                46)}},
                // 45
                {22268, 672, 582, {CCargo(149, 6, 25),   CCargo(447, 42, 10),  CCargo(607, 19, 30),  CCargo(1807, 40,
                                                                                                            43), CCargo(
                        269, 33, 8),   CCargo(1184, 35, 37), CCargo(544, 36, 16),  CCargo(360, 15, 22),  CCargo(79, 3,
                                                                                                                26), CCargo(
                        313, 17, 19),  CCargo(564, 23, 23),  CCargo(678, 47, 16),  CCargo(1312, 39, 33), CCargo(739, 31,
                                                                                                                24), CCargo(
                        135, 19, 7),   CCargo(1905, 49, 40), CCargo(111, 4, 27),   CCargo(586, 16, 40),  CCargo(586, 14,
                                                                                                                41), CCargo(
                        413, 42, 9),   CCargo(335, 11, 31),  CCargo(90, 3, 29),    CCargo(74, 4, 19),    CCargo(1688,
                                                                                                                33,
                                                                                                                48), CCargo(
                        156, 8, 18),   CCargo(659, 37, 17),  CCargo(114, 6, 20),   CCargo(1182, 38, 34), CCargo(2136,
                                                                                                                43,
                                                                                                                46), CCargo(
                        853, 24, 39),  CCargo(1142, 23, 48), CCargo(81, 43, 2),    CCargo(147, 29, 5),   CCargo(1715,
                                                                                                                47,
                                                                                                                36), CCargo(
                        1819, 40, 42), CCargo(1053, 37, 30), CCargo(872, 25, 34),  CCargo(841, 38, 23),  CCargo(623, 41,
                                                                                                                16), CCargo(
                        1273, 37, 38), CCargo(396, 40, 11),  CCargo(108, 24, 5),   CCargo(1090, 36, 33), CCargo(559, 17,
                                                                                                                31), CCargo(
                        974, 45, 21)}},
                {24077, 721, 660, {CCargo(1244, 35, 39), CCargo(377, 8, 48),   CCargo(1685, 38, 44), CCargo(364, 10,
                                                                                                            34), CCargo(
                        308, 13, 23),  CCargo(536, 12, 47),  CCargo(1727, 45, 35), CCargo(1482, 36, 39), CCargo(461, 23,
                                                                                                                19), CCargo(
                        878, 31, 28),  CCargo(289, 23, 13),  CCargo(476, 26, 19),  CCargo(347, 46, 8),   CCargo(414, 24,
                                                                                                                16), CCargo(
                        445, 17, 27),  CCargo(1783, 49, 38), CCargo(484, 13, 34),  CCargo(274, 13, 20),  CCargo(75, 2,
                                                                                                                41), CCargo(
                        910, 40, 22),  CCargo(905, 19, 44),  CCargo(722, 36, 21),  CCargo(50, 3, 17),    CCargo(541, 13,
                                                                                                                40), CCargo(
                        59, 9, 7),     CCargo(157, 25, 7),   CCargo(787, 40, 19),  CCargo(1068, 39, 30), CCargo(935, 28,
                                                                                                                31), CCargo(
                        689, 34, 21),  CCargo(661, 18, 39),  CCargo(357, 14, 25),  CCargo(792, 28, 26),  CCargo(1911,
                                                                                                                48,
                                                                                                                38), CCargo(
                        1641, 34, 45), CCargo(1058, 46, 21), CCargo(489, 46, 11),  CCargo(1620, 31, 48), CCargo(929, 34,
                                                                                                                27), CCargo(
                        349, 29, 11),  CCargo(1323, 45, 28), CCargo(271, 7, 41),   CCargo(738, 37, 19),  CCargo(580, 34,
                                                                                                                17), CCargo(
                        43, 22, 2),    CCargo(737, 15, 46)}},
                {17340, 496, 577, {CCargo(447, 21, 23),  CCargo(769, 24, 33),  CCargo(876, 22, 37),  CCargo(156, 3,
                                                                                                            49), CCargo(
                        73, 24, 3),    CCargo(495, 48, 10),  CCargo(590, 40, 14),  CCargo(213, 42, 5),   CCargo(1810,
                                                                                                                45,
                                                                                                                38), CCargo(
                        852, 21, 40),  CCargo(86, 8, 12),    CCargo(491, 14, 34),  CCargo(213, 31, 7),   CCargo(229, 26,
                                                                                                                9),  CCargo(
                        520, 17, 31),  CCargo(1331, 45, 29), CCargo(621, 29, 20),  CCargo(254, 18, 13),  CCargo(382, 46,
                                                                                                                8),  CCargo(
                        1038, 37, 28), CCargo(567, 16, 34),  CCargo(812, 18, 46),  CCargo(56, 2, 28),    CCargo(90, 22,
                                                                                                                4),  CCargo(
                        744, 41, 19),  CCargo(210, 14, 14),  CCargo(1674, 43, 41), CCargo(368, 37, 10),  CCargo(244, 34,
                                                                                                                7),  CCargo(
                        786, 20, 42),  CCargo(424, 44, 9),   CCargo(819, 31, 25),  CCargo(48, 2, 25),    CCargo(1215,
                                                                                                                27,
                                                                                                                46), CCargo(
                        440, 11, 38),  CCargo(45, 25, 2),    CCargo(849, 18, 44),  CCargo(870, 30, 32),  CCargo(89, 6,
                                                                                                                16), CCargo(
                        1343, 36, 34), CCargo(1213, 45, 29), CCargo(390, 38, 10),  CCargo(285, 28, 11),  CCargo(1483,
                                                                                                                44,
                                                                                                                37), CCargo(
                        748, 15, 47),  CCargo(93, 4, 22),    CCargo(198, 5, 38)}},
                {21751, 767, 520, {CCargo(478, 48, 10),  CCargo(2297, 49, 48), CCargo(988, 27, 40),  CCargo(1344, 37,
                                                                                                            34), CCargo(
                        94, 5, 19),    CCargo(2381, 45, 49), CCargo(83, 39, 2),    CCargo(441, 15, 31),  CCargo(199, 23,
                                                                                                                9),  CCargo(
                        834, 41, 22),  CCargo(500, 26, 20),  CCargo(937, 49, 20),  CCargo(844, 20, 46),  CCargo(833, 24,
                                                                                                                33), CCargo(
                        533, 16, 36),  CCargo(1185, 40, 32), CCargo(715, 35, 22),  CCargo(1136, 30, 36), CCargo(399, 41,
                                                                                                                9),  CCargo(
                        379, 8, 49),   CCargo(407, 15, 26),  CCargo(719, 30, 26),  CCargo(1716, 43, 44), CCargo(896, 48,
                                                                                                                18), CCargo(
                        1201, 37, 33), CCargo(942, 43, 24),  CCargo(440, 49, 9),   CCargo(313, 9, 37),   CCargo(1269,
                                                                                                                45,
                                                                                                                29), CCargo(
                        1434, 41, 36), CCargo(525, 10, 49),  CCargo(1313, 45, 30), CCargo(45, 2, 24),    CCargo(89, 4,
                                                                                                                22), CCargo(
                        325, 38, 9),   CCargo(31, 10, 3),    CCargo(42, 13, 3),    CCargo(379, 37, 10),  CCargo(265, 47,
                                                                                                                6),  CCargo(
                        850, 17, 46),  CCargo(221, 34, 6),   CCargo(1377, 28, 49), CCargo(100, 46, 2),   CCargo(49, 10,
                                                                                                                5),  CCargo(
                        1621, 39, 41), CCargo(8, 4, 2),      CCargo(521, 39, 13),  CCargo(1772, 34, 49)}},
                {17007, 558, 457, {CCargo(427, 12, 34),  CCargo(301, 26, 12),  CCargo(956, 22, 40),  CCargo(244, 40,
                                                                                                            6),  CCargo(
                        548, 16, 36),  CCargo(442, 37, 11),  CCargo(1064, 33, 32), CCargo(388, 47, 8),   CCargo(502, 35,
                                                                                                                15), CCargo(
                        38, 2, 21),    CCargo(1252, 38, 31), CCargo(188, 26, 8),   CCargo(1254, 42, 28), CCargo(806, 39,
                                                                                                                19), CCargo(
                        679, 20, 33),  CCargo(706, 33, 20),  CCargo(119, 30, 4),   CCargo(16, 8, 2),     CCargo(1559,
                                                                                                                40,
                                                                                                                36), CCargo(
                        208, 6, 36),   CCargo(353, 13, 25),  CCargo(7, 4, 2),      CCargo(258, 6, 42),   CCargo(1649,
                                                                                                                47,
                                                                                                                32), CCargo(
                        135, 44, 3),   CCargo(833, 27, 34),  CCargo(257, 20, 14),  CCargo(851, 44, 21),  CCargo(316, 27,
                                                                                                                11), CCargo(
                        371, 23, 16),  CCargo(956, 39, 27),  CCargo(980, 36, 30),  CCargo(1472, 39, 35), CCargo(676, 21,
                                                                                                                32), CCargo(
                        573, 21, 27),  CCargo(15, 4, 4),     CCargo(138, 6, 23),   CCargo(214, 11, 18),  CCargo(648, 16,
                                                                                                                44), CCargo(
                        141, 8, 18),   CCargo(258, 34, 7),   CCargo(1487, 36, 41), CCargo(1115, 38, 31), CCargo(106, 33,
                                                                                                                3),  CCargo(
                        247, 11, 23),  CCargo(941, 38, 25),  CCargo(62, 2, 29),    CCargo(939, 26, 38),  CCargo(97, 21,
                                                                                                                5)}},
                // 50
                {22825, 610, 744, {CCargo(875, 36, 26),  CCargo(822, 33, 27),  CCargo(341, 39, 9),   CCargo(47, 4,
                                                                                                            12), CCargo(
                        1601, 43, 39), CCargo(137, 23, 6),   CCargo(2100, 47, 48), CCargo(298, 27, 12),  CCargo(610, 13,
                                                                                                                44), CCargo(
                        1284, 46, 31), CCargo(831, 46, 18),  CCargo(266, 6, 49),   CCargo(439, 12, 39),  CCargo(1168,
                                                                                                                29,
                                                                                                                41), CCargo(
                        65, 2, 35),    CCargo(115, 15, 8),   CCargo(217, 38, 6),   CCargo(1420, 46, 31), CCargo(122, 3,
                                                                                                                42), CCargo(
                        1792, 43, 38), CCargo(1445, 44, 34), CCargo(788, 21, 39),  CCargo(1034, 23, 49), CCargo(971, 32,
                                                                                                                28), CCargo(
                        118, 4, 29),   CCargo(615, 14, 42),  CCargo(956, 29, 31),  CCargo(1091, 41, 27), CCargo(442, 16,
                                                                                                                29), CCargo(
                        698, 35, 22),  CCargo(602, 34, 17),  CCargo(71, 2, 36),    CCargo(152, 17, 9),   CCargo(799, 22,
                                                                                                                40), CCargo(
                        790, 18, 43),  CCargo(326, 47, 7),   CCargo(1088, 35, 34), CCargo(691, 26, 26),  CCargo(1805,
                                                                                                                47,
                                                                                                                41), CCargo(
                        319, 12, 26),  CCargo(167, 14, 11),  CCargo(543, 48, 11),  CCargo(687, 24, 27),  CCargo(2255,
                                                                                                                47,
                                                                                                                47), CCargo(
                        777, 49, 16),  CCargo(396, 30, 13),  CCargo(178, 4, 47),   CCargo(202, 8, 24),   CCargo(813, 38,
                                                                                                                21), CCargo(
                        1386, 47, 32)}},
                {17813, 632, 472, {CCargo(631, 22, 30),  CCargo(209, 25, 8),   CCargo(239, 8, 31),   CCargo(308, 7,
                                                                                                            42), CCargo(
                        427, 12, 34),  CCargo(301, 26, 12),  CCargo(956, 22, 40),  CCargo(244, 40, 6),   CCargo(548, 16,
                                                                                                                36), CCargo(
                        442, 37, 11),  CCargo(1064, 33, 32), CCargo(388, 47, 8),   CCargo(502, 35, 15),  CCargo(38, 2,
                                                                                                                21), CCargo(
                        1252, 38, 31), CCargo(188, 26, 8),   CCargo(1254, 42, 28), CCargo(806, 39, 19),  CCargo(679, 20,
                                                                                                                33), CCargo(
                        706, 33, 20),  CCargo(119, 30, 4),   CCargo(16, 8, 2),     CCargo(1559, 40, 36), CCargo(208, 6,
                                                                                                                36), CCargo(
                        353, 13, 25),  CCargo(7, 4, 2),      CCargo(258, 6, 42),   CCargo(1649, 47, 32), CCargo(135, 44,
                                                                                                                3),  CCargo(
                        833, 27, 34),  CCargo(257, 20, 14),  CCargo(851, 44, 21),  CCargo(316, 27, 11),  CCargo(371, 23,
                                                                                                                16), CCargo(
                        956, 39, 27),  CCargo(980, 36, 30),  CCargo(1472, 39, 35), CCargo(676, 21, 32),  CCargo(573, 21,
                                                                                                                27), CCargo(
                        15, 4, 4),     CCargo(138, 6, 23),   CCargo(214, 11, 18),  CCargo(648, 16, 44),  CCargo(141, 8,
                                                                                                                18), CCargo(
                        258, 34, 7),   CCargo(1487, 36, 41), CCargo(1115, 38, 31), CCargo(106, 33, 3),   CCargo(247, 11,
                                                                                                                23), CCargo(
                        941, 38, 25),  CCargo(62, 2, 29)}},
                {22628, 564, 768, {CCargo(778, 25, 30),  CCargo(1451, 37, 37), CCargo(251, 6, 40),   CCargo(1324, 29,
                                                                                                            49), CCargo(
                        458, 11, 39),  CCargo(1244, 35, 39), CCargo(377, 8, 48),   CCargo(1685, 38, 44), CCargo(364, 10,
                                                                                                                34), CCargo(
                        308, 13, 23),  CCargo(536, 12, 47),  CCargo(1727, 45, 35), CCargo(1482, 36, 39), CCargo(461, 23,
                                                                                                                19), CCargo(
                        878, 31, 28),  CCargo(289, 23, 13),  CCargo(476, 26, 19),  CCargo(347, 46, 8),   CCargo(414, 24,
                                                                                                                16), CCargo(
                        445, 17, 27),  CCargo(1783, 49, 38), CCargo(484, 13, 34),  CCargo(274, 13, 20),  CCargo(75, 2,
                                                                                                                41), CCargo(
                        910, 40, 22),  CCargo(905, 19, 44),  CCargo(722, 36, 21),  CCargo(50, 3, 17),    CCargo(541, 13,
                                                                                                                40), CCargo(
                        59, 9, 7),     CCargo(157, 25, 7),   CCargo(787, 40, 19),  CCargo(1068, 39, 30), CCargo(935, 28,
                                                                                                                31), CCargo(
                        689, 34, 21),  CCargo(661, 18, 39),  CCargo(357, 14, 25),  CCargo(792, 28, 26),  CCargo(1911,
                                                                                                                48,
                                                                                                                38), CCargo(
                        1641, 34, 45), CCargo(1058, 46, 21), CCargo(489, 46, 11),  CCargo(1620, 31, 48), CCargo(929, 34,
                                                                                                                27), CCargo(
                        349, 29, 11),  CCargo(1323, 45, 28), CCargo(271, 7, 41),   CCargo(738, 37, 19),  CCargo(580, 34,
                                                                                                                17), CCargo(
                        43, 22, 2),    CCargo(737, 15, 46),  CCargo(547, 14, 43)}},
                {24673, 692, 680, {CCargo(240, 24, 10),  CCargo(815, 20, 42),  CCargo(234, 36, 7),   CCargo(854, 34,
                                                                                                            25), CCargo(
                        238, 27, 9),   CCargo(232, 13, 18),  CCargo(392, 14, 28),  CCargo(1027, 30, 37), CCargo(139, 11,
                                                                                                                12), CCargo(
                        343, 34, 11),  CCargo(227, 7, 34),   CCargo(114, 31, 4),   CCargo(1780, 48, 39), CCargo(201, 8,
                                                                                                                24), CCargo(
                        1749, 33, 49), CCargo(57, 5, 12),    CCargo(742, 28, 25),  CCargo(20, 4, 5),     CCargo(157, 10,
                                                                                                                15), CCargo(
                        2570, 49, 48), CCargo(30, 6, 5),     CCargo(690, 19, 35),  CCargo(878, 26, 34),  CCargo(1649,
                                                                                                                38,
                                                                                                                40), CCargo(
                        675, 26, 24),  CCargo(549, 22, 27),  CCargo(173, 34, 5),   CCargo(207, 25, 8),   CCargo(52, 3,
                                                                                                                16), CCargo(
                        695, 40, 16),  CCargo(684, 38, 20),  CCargo(829, 21, 38),  CCargo(81, 6, 14),    CCargo(81, 29,
                                                                                                                3),  CCargo(
                        717, 25, 28),  CCargo(938, 21, 48),  CCargo(841, 27, 33),  CCargo(69, 9, 8),     CCargo(433, 42,
                                                                                                                10), CCargo(
                        2151, 41, 48), CCargo(1327, 37, 37), CCargo(280, 38, 8),   CCargo(269, 23, 12),  CCargo(1571,
                                                                                                                41,
                                                                                                                39), CCargo(
                        803, 49, 15),  CCargo(1179, 31, 35), CCargo(475, 39, 12),  CCargo(39, 2, 19),    CCargo(245, 19,
                                                                                                                12), CCargo(
                        9, 3, 3),      CCargo(1943, 49, 39), CCargo(507, 18, 27),  CCargo(1280, 24, 49)}},
                {27567, 790, 784, {CCargo(987, 25, 40),  CCargo(420, 33, 14),  CCargo(56, 11, 5),    CCargo(288, 11,
                                                                                                            27), CCargo(
                        287, 18, 17),  CCargo(55, 29, 2),    CCargo(1154, 30, 40), CCargo(2099, 49, 44), CCargo(1529,
                                                                                                                31,
                                                                                                                49), CCargo(
                        204, 40, 5),   CCargo(798, 29, 28),  CCargo(24, 2, 12),    CCargo(92, 4, 22),    CCargo(1070,
                                                                                                                35,
                                                                                                                32), CCargo(
                        250, 5, 49),   CCargo(401, 14, 28),  CCargo(228, 29, 8),   CCargo(295, 44, 7),   CCargo(495, 14,
                                                                                                                37), CCargo(
                        1048, 40, 27), CCargo(136, 21, 6),   CCargo(266, 41, 7),   CCargo(228, 25, 9),   CCargo(567, 14,
                                                                                                                43), CCargo(
                        1164, 27, 46), CCargo(92, 8, 11),    CCargo(1590, 38, 39), CCargo(397, 11, 33),  CCargo(1173,
                                                                                                                25,
                                                                                                                45), CCargo(
                        1333, 39, 36), CCargo(54, 8, 7),     CCargo(182, 4, 46),   CCargo(248, 11, 22),  CCargo(1324,
                                                                                                                39,
                                                                                                                34), CCargo(
                        579, 49, 12),  CCargo(214, 11, 19),  CCargo(316, 46, 7),   CCargo(605, 39, 17),  CCargo(1709,
                                                                                                                39,
                                                                                                                40), CCargo(
                        778, 25, 30),  CCargo(1451, 37, 37), CCargo(251, 6, 40),   CCargo(1324, 29, 49), CCargo(458, 11,
                                                                                                                39), CCargo(
                        1244, 35, 39), CCargo(377, 8, 48),   CCargo(1685, 38, 44), CCargo(364, 10, 34),  CCargo(308, 13,
                                                                                                                23), CCargo(
                        536, 12, 47),  CCargo(1727, 45, 35), CCargo(1482, 36, 39), CCargo(461, 23, 19),  CCargo(878, 31,
                                                                                                                28)}},
                // 55
                {21670, 719, 604, {CCargo(2058, 46, 44), CCargo(1268, 43, 30), CCargo(362, 21, 19),  CCargo(90, 33,
                                                                                                            3),  CCargo(
                        325, 27, 12),  CCargo(2030, 46, 49), CCargo(996, 20, 49),  CCargo(403, 16, 26),  CCargo(1239,
                                                                                                                28,
                                                                                                                45), CCargo(
                        787, 35, 22),  CCargo(189, 10, 19),  CCargo(452, 38, 13),  CCargo(326, 10, 33),  CCargo(190, 12,
                                                                                                                16), CCargo(
                        698, 16, 42),  CCargo(1658, 41, 39), CCargo(391, 42, 9),   CCargo(494, 22, 24),  CCargo(71, 39,
                                                                                                                2),  CCargo(
                        398, 11, 36),  CCargo(1946, 41, 44), CCargo(489, 16, 33),  CCargo(868, 20, 41),  CCargo(154, 42,
                                                                                                                4),  CCargo(
                        351, 17, 19),  CCargo(20, 2, 10),    CCargo(116, 36, 3),   CCargo(445, 20, 23),  CCargo(337, 29,
                                                                                                                12), CCargo(
                        652, 34, 21),  CCargo(144, 11, 12),  CCargo(165, 6, 27),   CCargo(590, 13, 46),  CCargo(113, 3,
                                                                                                                38), CCargo(
                        51, 8, 6),     CCargo(38, 6, 7),     CCargo(1531, 41, 41), CCargo(385, 35, 11),  CCargo(122, 3,
                                                                                                                39), CCargo(
                        447, 21, 23),  CCargo(769, 24, 33),  CCargo(876, 22, 37),  CCargo(156, 3, 49),   CCargo(73, 24,
                                                                                                                3),  CCargo(
                        495, 48, 10),  CCargo(590, 40, 14),  CCargo(213, 42, 5),   CCargo(1810, 45, 38), CCargo(852, 21,
                                                                                                                40), CCargo(
                        86, 8, 12),    CCargo(491, 14, 34),  CCargo(213, 31, 7),   CCargo(229, 26, 9),   CCargo(520, 17,
                                                                                                                31), CCargo(
                        1331, 45, 29)}},
                {25933, 672, 678, {CCargo(1849, 47, 42), CCargo(61, 33, 2),    CCargo(90, 49, 2),    CCargo(905, 23,
                                                                                                            39), CCargo(
                        323, 23, 13),  CCargo(177, 19, 10),  CCargo(1391, 47, 30), CCargo(310, 30, 11),  CCargo(49, 8,
                                                                                                                6),  CCargo(
                        766, 17, 45),  CCargo(1305, 32, 42), CCargo(996, 41, 25),  CCargo(1190, 49, 25), CCargo(261, 6,
                                                                                                                47), CCargo(
                        625, 32, 20),  CCargo(1077, 28, 38), CCargo(1171, 36, 35), CCargo(131, 9, 15),   CCargo(412, 19,
                                                                                                                22), CCargo(
                        143, 4, 37),   CCargo(542, 29, 20),  CCargo(524, 46, 11),  CCargo(140, 15, 10),  CCargo(413, 32,
                                                                                                                14), CCargo(
                        1753, 39, 45), CCargo(218, 10, 23),  CCargo(402, 37, 10),  CCargo(724, 45, 17),  CCargo(507, 14,
                                                                                                                35), CCargo(
                        1274, 35, 37), CCargo(50, 3, 16),    CCargo(129, 12, 12),  CCargo(1096, 45, 26), CCargo(44, 5,
                                                                                                                9),  CCargo(
                        502, 11, 47),  CCargo(259, 35, 7),   CCargo(2212, 47, 43), CCargo(1605, 44, 38), CCargo(17, 8,
                                                                                                                2),  CCargo(
                        1506, 40, 36), CCargo(448, 13, 38),  CCargo(139, 3, 49),   CCargo(139, 3, 44),   CCargo(624, 12,
                                                                                                                48), CCargo(
                        327, 34, 9),   CCargo(137, 3, 42),   CCargo(1794, 42, 40), CCargo(1421, 41, 34), CCargo(286, 7,
                                                                                                                40), CCargo(
                        210, 7, 31),   CCargo(1622, 42, 42), CCargo(1773, 44, 44), CCargo(452, 9, 46),   CCargo(400, 46,
                                                                                                                8),  CCargo(
                        1585, 42, 41), CCargo(1641, 35, 43)}},
                {22901, 788, 602, {CCargo(849, 18, 44),  CCargo(870, 30, 32),  CCargo(89, 6, 16),    CCargo(1343, 36,
                                                                                                            34), CCargo(
                        1213, 45, 29), CCargo(390, 38, 10),  CCargo(285, 28, 11),  CCargo(1483, 44, 37), CCargo(748, 15,
                                                                                                                47), CCargo(
                        93, 4, 22),    CCargo(198, 5, 38),   CCargo(866, 47, 19),  CCargo(1137, 48, 23), CCargo(60, 7,
                                                                                                                9),  CCargo(
                        30, 7, 4),     CCargo(526, 14, 41),  CCargo(819, 45, 19),  CCargo(50, 4, 14),    CCargo(177, 6,
                                                                                                                27), CCargo(
                        1323, 45, 30), CCargo(1176, 37, 34), CCargo(718, 23, 31),  CCargo(1316, 40, 30), CCargo(803, 24,
                                                                                                                36), CCargo(
                        1582, 40, 42), CCargo(190, 35, 6),   CCargo(76, 39, 2),    CCargo(20, 5, 4),     CCargo(58, 7,
                                                                                                                9),  CCargo(
                        31, 6, 5),     CCargo(987, 25, 40),  CCargo(420, 33, 14),  CCargo(56, 11, 5),    CCargo(288, 11,
                                                                                                                27), CCargo(
                        287, 18, 17),  CCargo(55, 29, 2),    CCargo(1154, 30, 40), CCargo(2099, 49, 44), CCargo(1529,
                                                                                                                31,
                                                                                                                49), CCargo(
                        204, 40, 5),   CCargo(798, 29, 28),  CCargo(24, 2, 12),    CCargo(92, 4, 22),    CCargo(1070,
                                                                                                                35,
                                                                                                                32), CCargo(
                        250, 5, 49),   CCargo(401, 14, 28),  CCargo(228, 29, 8),   CCargo(295, 44, 7),   CCargo(495, 14,
                                                                                                                37), CCargo(
                        1048, 40, 27), CCargo(136, 21, 6),   CCargo(266, 41, 7),   CCargo(228, 25, 9),   CCargo(567, 14,
                                                                                                                43), CCargo(
                        1164, 27, 46), CCargo(92, 8, 11),  CCargo(1590, 38, 39)}},
                {25064, 859, 760, {CCargo(221, 34, 6),   CCargo(1377, 28, 49), CCargo(100, 46, 2),   CCargo(49, 10,
                                                                                                            5),  CCargo(
                        1621, 39, 41), CCargo(8, 4, 2),      CCargo(521, 39, 13),  CCargo(1772, 34, 49), CCargo(865, 17,
                                                                                                                47), CCargo(
                        403, 27, 14),  CCargo(1223, 24, 47), CCargo(568, 21, 25),  CCargo(1049, 46, 21), CCargo(1215,
                                                                                                                45,
                                                                                                                30), CCargo(
                        344, 17, 19),  CCargo(1031, 44, 22), CCargo(261, 26, 11),  CCargo(321, 8, 44),   CCargo(476, 48,
                                                                                                                11), CCargo(
                        1512, 44, 36), CCargo(374, 36, 11),  CCargo(1033, 33, 30), CCargo(725, 29, 27),  CCargo(600, 25,
                                                                                                                23), CCargo(
                        906, 26, 38),  CCargo(562, 17, 33),  CCargo(84, 9, 9),     CCargo(211, 13, 16),  CCargo(251, 17,
                                                                                                                14), CCargo(
                        161, 18, 9),   CCargo(1382, 31, 43), CCargo(1046, 42, 26), CCargo(149, 28, 5),   CCargo(967, 35,
                                                                                                                29), CCargo(
                        95, 21, 5),    CCargo(566, 26, 21),  CCargo(61, 2, 29),    CCargo(1369, 36, 41), CCargo(133, 17,
                                                                                                                8),  CCargo(
                        145, 6, 24),   CCargo(177, 30, 6),   CCargo(752, 15, 46),  CCargo(657, 29, 25),  CCargo(204, 20,
                                                                                                                10), CCargo(
                        1027, 33, 30), CCargo(193, 35, 6),   CCargo(145, 20, 7),   CCargo(504, 12, 42),  CCargo(175, 19,
                                                                                                                9),  CCargo(
                        468, 39, 13),  CCargo(694, 18, 41),  CCargo(246, 38, 7),   CCargo(1253, 36, 34), CCargo(201, 38,
                                                                                                                5),  CCargo(
                        669, 19, 36),  CCargo(109, 5, 22), CCargo(408, 10, 40), CCargo(83, 42, 2)}},
                {22461, 654, 630, {CCargo(1149, 28, 39), CCargo(1336, 36, 40), CCargo(172, 34, 5),   CCargo(171, 10,
                                                                                                            19), CCargo(
                        61, 2, 28),    CCargo(149, 7, 23),   CCargo(1364, 45, 33), CCargo(112, 17, 7),   CCargo(656, 13,
                                                                                                                46), CCargo(
                        1095, 27, 45), CCargo(203, 8, 24),   CCargo(503, 45, 11),  CCargo(177, 4, 43),   CCargo(112, 31,
                                                                                                                4),  CCargo(
                        130, 32, 4),   CCargo(252, 31, 9),   CCargo(197, 38, 5),   CCargo(909, 43, 20),  CCargo(226, 7,
                                                                                                                31), CCargo(
                        55, 6, 9),     CCargo(96, 7, 15),    CCargo(475, 45, 11),  CCargo(303, 25, 13),  CCargo(356, 9,
                                                                                                                42), CCargo(
                        251, 11, 24),  CCargo(236, 40, 6),   CCargo(1764, 41, 43), CCargo(1009, 26, 36), CCargo(674, 16,
                                                                                                                42), CCargo(
                        145, 3, 47),   CCargo(148, 34, 4),   CCargo(1704, 39, 47), CCargo(134, 6, 23),   CCargo(410, 14,
                                                                                                                31), CCargo(
                        1025, 24, 41), CCargo(1218, 37, 31), CCargo(227, 10, 22),  CCargo(1566, 34, 47), CCargo(384, 29,
                                                                                                                14), CCargo(
                        84, 6, 15),    CCargo(1723, 38, 48), CCargo(1246, 36, 37), CCargo(1808, 43, 41), CCargo(79, 14,
                                                                                                                6),  CCargo(
                        637, 25, 28),  CCargo(170, 11, 15),  CCargo(42, 2, 23),    CCargo(221, 35, 7),   CCargo(200, 6,
                                                                                                                35), CCargo(
                        711, 18, 39),  CCargo(706, 26, 27),  CCargo(459, 37, 13),  CCargo(297, 46, 7),   CCargo(499, 28,
                                                                                                                19), CCargo(
                        1804, 40, 43), CCargo(151, 42, 4), CCargo(129, 26, 5),  CCargo(1160, 30, 38), CCargo(1315, 32,
                                                                                                             43)}}
        };

