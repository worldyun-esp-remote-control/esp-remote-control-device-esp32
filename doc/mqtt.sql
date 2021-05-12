/*
 Navicat Premium Data Transfer

 Source Server         : mqtt
 Source Server Type    : MySQL
 Source Server Version : 50733
 Source Host           : worldyun.xyz:3306
 Source Schema         : mqtt

 Target Server Type    : MySQL
 Target Server Version : 50733
 File Encoding         : 65001

 Date: 12/05/2021 18:51:26
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for mqtt_acl
-- ----------------------------
DROP TABLE IF EXISTS `mqtt_acl`;
CREATE TABLE `mqtt_acl`  (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `allow` int(1) NULL DEFAULT NULL COMMENT '0: deny, 1: allow',
  `ipaddr` varchar(60) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT 'IpAddress',
  `username` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT 'Username',
  `clientid` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT 'ClientId',
  `access` int(2) NOT NULL COMMENT '1: subscribe, 2: publish, 3: pubsub',
  `topic` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT 'Topic Filter',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 7 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of mqtt_acl
-- ----------------------------
INSERT INTO `mqtt_acl` VALUES (1, 1, NULL, 'esp-device', NULL, 1, '/device/%c');
INSERT INTO `mqtt_acl` VALUES (2, 1, NULL, 'esp-device', NULL, 2, '/upload');
INSERT INTO `mqtt_acl` VALUES (3, 1, NULL, 'server', NULL, 2, '/device/#');
INSERT INTO `mqtt_acl` VALUES (4, 1, NULL, 'server', NULL, 1, '/upload');
INSERT INTO `mqtt_acl` VALUES (5, 1, NULL, 'esp-device', NULL, 2, '/learn');
INSERT INTO `mqtt_acl` VALUES (6, 1, NULL, 'server', NULL, 1, '/learn');

-- ----------------------------
-- Table structure for mqtt_user
-- ----------------------------
DROP TABLE IF EXISTS `mqtt_user`;
CREATE TABLE `mqtt_user`  (
  `id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT,
  `username` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `password` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `salt` varchar(20) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `is_superuser` tinyint(1) NULL DEFAULT 0,
  `created` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `mqtt_username`(`username`) USING BTREE
) ENGINE = MyISAM AUTO_INCREMENT = 4 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of mqtt_user
-- ----------------------------
INSERT INTO `mqtt_user` VALUES (1, 'admin', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', NULL, 1, '2021-05-04 12:16:34');
INSERT INTO `mqtt_user` VALUES (2, 'esp-device', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', NULL, 0, '2021-05-04 12:17:51');
INSERT INTO `mqtt_user` VALUES (3, 'server', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', NULL, 0, '2021-05-05 15:42:34');

SET FOREIGN_KEY_CHECKS = 1;
