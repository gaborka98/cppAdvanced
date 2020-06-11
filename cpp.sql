/*
 Navicat Premium Data Transfer

 Source Server         : Local
 Source Server Type    : MySQL
 Source Server Version : 80019
 Source Host           : localhost:3306
 Source Schema         : cpp

 Target Server Type    : MySQL
 Target Server Version : 80019
 File Encoding         : 65001

 Date: 03/06/2020 08:57:16
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for event_type
-- ----------------------------
DROP TABLE IF EXISTS `event_type`;
CREATE TABLE `event_type` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) COLLATE utf8_hungarian_ci NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8 COLLATE=utf8_hungarian_ci;

-- ----------------------------
-- Records of event_type
-- ----------------------------
BEGIN;
INSERT INTO `event_type` VALUES (1, 'Like');
INSERT INTO `event_type` VALUES (2, 'Dislike');
INSERT INTO `event_type` VALUES (3, 'Watched');
INSERT INTO `event_type` VALUES (4, 'Score');
COMMIT;

-- ----------------------------
-- Table structure for film_events
-- ----------------------------
DROP TABLE IF EXISTS `film_events`;
CREATE TABLE `film_events` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Type_id` int NOT NULL,
  `User_id` int NOT NULL,
  `Film_id` int NOT NULL,
  `Score` int DEFAULT NULL COMMENT 'Csak a pontszamnal vesszuk hasznat',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 COLLATE=utf8_hungarian_ci;

-- ----------------------------
-- Records of film_events
-- ----------------------------
BEGIN;
INSERT INTO `film_events` VALUES (1, 1, 1, 3, NULL);
INSERT INTO `film_events` VALUES (2, 2, 1, 2, NULL);
INSERT INTO `film_events` VALUES (3, 3, 1, 5, NULL);
INSERT INTO `film_events` VALUES (4, 4, 1, 5, 7);
INSERT INTO `film_events` VALUES (5, 4, 1, 5, 9);
INSERT INTO `film_events` VALUES (6, 3, 1, 5, NULL);
INSERT INTO `film_events` VALUES (8, 3, 1, 5, NULL);
COMMIT;

-- ----------------------------
-- Table structure for films
-- ----------------------------
DROP TABLE IF EXISTS `films`;
CREATE TABLE `films` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Title` varchar(255) CHARACTER SET utf8 COLLATE utf8_hungarian_ci NOT NULL,
  `Original_title` varchar(255) CHARACTER SET utf8 COLLATE utf8_hungarian_ci DEFAULT NULL,
  `Category` varchar(255) CHARACTER SET utf8 COLLATE utf8_hungarian_ci DEFAULT NULL,
  `Score` double(3,0) DEFAULT NULL,
  `Watched` int DEFAULT NULL,
  `Lenght` int DEFAULT NULL,
  `Audio` varchar(3) CHARACTER SET utf8 COLLATE utf8_hungarian_ci DEFAULT NULL,
  `Subtitle` varchar(3) CHARACTER SET utf8 COLLATE utf8_hungarian_ci DEFAULT NULL,
  `Likes` int DEFAULT NULL,
  `Dislikes` varchar(4) COLLATE utf8_hungarian_ci DEFAULT NULL,
  PRIMARY KEY (`ID`) USING BTREE
) ENGINE=MyISAM AUTO_INCREMENT=17 DEFAULT CHARSET=utf8 COLLATE=utf8_hungarian_ci;

-- ----------------------------
-- Records of films
-- ----------------------------
BEGIN;
INSERT INTO `films` VALUES (1, 'Drágán add az életed', 'Die Hard', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (2, 'Casino royale', 'Casino Royale', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (3, 'Első 50 randi', NULL, 'romantikus', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (4, 'Thor - Ragnarök', NULL, 'sci-fi', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (5, 'Csillagok közt', NULL, 'sci-fi', 8, 3, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (7, 'Peaky Blinders S01E02', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (6, 'Peaky Blinders S01E01', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (8, 'Peaky Blinders S01E03', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (9, 'Peaky Blinders S01E04', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (10, 'Peaky Blinders S01E05', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (11, 'Peaky Blinders S02E01', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (12, 'Peaky Blinders S02E02', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (13, 'Peaky Blinders S02E03', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (14, 'Peaky Blinders S02E04', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (15, 'Peaky Blinders S02E05', 'Peaky Blinders', 'akció', NULL, NULL, NULL, NULL, NULL, NULL, NULL);
INSERT INTO `films` VALUES (16, 'tesz ESB', 'asddsaasd', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
COMMIT;

-- ----------------------------
-- Table structure for users
-- ----------------------------
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `ID` int NOT NULL AUTO_INCREMENT,
  `Real_name` varchar(255) COLLATE utf8_hungarian_ci DEFAULT NULL,
  `Username` varchar(255) COLLATE utf8_hungarian_ci NOT NULL,
  `Email` varchar(255) COLLATE utf8_hungarian_ci NOT NULL,
  `Password` varchar(160) COLLATE utf8_hungarian_ci NOT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COLLATE=utf8_hungarian_ci;

-- ----------------------------
-- Records of users
-- ----------------------------
BEGIN;
INSERT INTO `users` VALUES (1, 'John Doe', 'test', 'john.doe@test.com', 'test');
COMMIT;

-- ----------------------------
-- View structure for calculate score
-- ----------------------------
DROP VIEW IF EXISTS `calculate score`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `calculate score` AS select sum(`film_events`.`Score`) AS `total`,count(`film_events`.`ID`) AS `db` from `film_events` where ((`film_events`.`Type_id` = 4) and (`film_events`.`Film_id` = 5)) group by `film_events`.`Type_id`;

-- ----------------------------
-- View structure for printfilmevent
-- ----------------------------
DROP VIEW IF EXISTS `printfilmevent`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `printfilmevent` AS select `films`.`Title` AS `Title`,`users`.`Username` AS `Username`,`event_type`.`Name` AS `Name` from (((`film_events` join `event_type` on((`film_events`.`Type_id` = `event_type`.`ID`))) join `users` on((`film_events`.`User_id` = `users`.`ID`))) join `films` on((`film_events`.`Film_id` = `films`.`ID`))) where ((`film_events`.`Type_id` = `event_type`.`ID`) and (`film_events`.`User_id` = `users`.`ID`) and (`film_events`.`Film_id` = `films`.`ID`));

-- ----------------------------
-- View structure for select only film
-- ----------------------------
DROP VIEW IF EXISTS `select only film`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `select only film` AS select `films`.`ID` AS `ID`,`films`.`Title` AS `Title`,`films`.`Original_title` AS `Original_title`,`films`.`Category` AS `Category`,`films`.`Score` AS `Score`,`films`.`Wached` AS `Wached`,`films`.`Lenght` AS `Lenght`,`films`.`Audio` AS `Audio`,`films`.`Subtitle` AS `Subtitle`,`films`.`Likes` AS `Likes`,`films`.`Dislikes` AS `Dislikes` from `films` where (not(regexp_like(`films`.`Title`,'.*E[0-9][0-9]')));

-- ----------------------------
-- View structure for select series
-- ----------------------------
DROP VIEW IF EXISTS `select series`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `select series` AS select `films`.`Original_title` AS `Original_title`,count(`films`.`Title`) AS `Episode_in_season` from `films` where regexp_like(`films`.`Title`,'S[0-9][0-9]E[0-9][0-9]') group by `films`.`Original_title`;

-- ----------------------------
-- View structure for select series episodes
-- ----------------------------
DROP VIEW IF EXISTS `select series episodes`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `select series episodes` AS select `films`.`Title` AS `Title` from `films` where (`films`.`Original_title` = 'Peaky Blinders S01') order by `films`.`Title`;

-- ----------------------------
-- View structure for select watched
-- ----------------------------
DROP VIEW IF EXISTS `select watched`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `select watched` AS select count(`films`.`Category`) AS `Count`,`films`.`Category` AS `Category` from (`film_events` join `films` on((`film_events`.`Film_id` = `films`.`ID`))) where ((`film_events`.`Type_id` = 3) and (`film_events`.`User_id` = 1)) group by `films`.`Category` order by `Count`;

-- ----------------------------
-- View structure for select watched max category
-- ----------------------------
DROP VIEW IF EXISTS `select watched max category`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `select watched max category` AS select count(`films`.`Category`) AS `Count`,`films`.`Category` AS `Category` from (`film_events` join `films` on((`film_events`.`Film_id` = `films`.`ID`))) where (`film_events`.`Type_id` = 3) group by `films`.`Category` order by `Count`;

-- ----------------------------
-- View structure for select watchedcount
-- ----------------------------
DROP VIEW IF EXISTS `select watchedcount`;
CREATE ALGORITHM = UNDEFINED SQL SECURITY DEFINER VIEW `select watchedcount` AS select count(`film_events`.`ID`) AS `COUNT( film_events.ID )` from `film_events` where ((`film_events`.`Type_id` = 3) and (`film_events`.`Film_id` = 5));

SET FOREIGN_KEY_CHECKS = 1;
