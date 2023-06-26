-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 23, 2023 at 11:05 PM
-- Server version: 10.4.27-MariaDB
-- PHP Version: 8.2.0

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `gestion_biblio`
--

-- --------------------------------------------------------

--
-- Table structure for table `appartientt`
--

CREATE TABLE `appartientt` (
  `ID_RAYON` int(11) NOT NULL,
  `ID_ETAGERE` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Table structure for table `auteur`
--

CREATE TABLE `auteur` (
  `ID_AUTEUR` int(11) NOT NULL,
  `NOM_AUTEUR` longtext NOT NULL,
  `DATENAISSANCEAUTEUR` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `auteur`
--

INSERT INTO `auteur` (`ID_AUTEUR`, `NOM_AUTEUR`, `DATENAISSANCEAUTEUR`) VALUES
(3, 'mostafa mahmoud', '1963-09-03'),
(4, 'jordan peterson', '1978-04-22'),
(5, 'jk rowling', '1970-02-23'),
(6, 'jon rr martin', '1955-04-10');

-- --------------------------------------------------------

--
-- Table structure for table `categorie`
--

CREATE TABLE `categorie` (
  `ID_CATEGORIE` int(11) NOT NULL,
  `LIBELLE_CATEGORIE` longtext NOT NULL,
  `photoCategorie` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `categorie`
--

INSERT INTO `categorie` (`ID_CATEGORIE`, `LIBELLE_CATEGORIE`, `photoCategorie`) VALUES
(1, 'Litterature', 'images/literature.jpg'),
(2, 'Histoire', 'images/history.jpg'),
(3, 'Horreur', 'images/horror.jpg');

-- --------------------------------------------------------

--
-- Table structure for table `empruntlivre`
--

CREATE TABLE `empruntlivre` (
  `ID_EMPRUNTE` int(11) NOT NULL,
  `ID_RESERVATION` int(11) NOT NULL,
  `DATEEMPRUNTE` datetime NOT NULL,
  `DATE_RETURN` datetime DEFAULT NULL,
  `DATE_RETURN_EMPRUNTE` datetime DEFAULT (`DATEEMPRUNTE` + interval 360 hour)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `empruntlivre`
--

INSERT INTO `empruntlivre` (`ID_EMPRUNTE`, `ID_RESERVATION`, `DATEEMPRUNTE`, `DATE_RETURN`, `DATE_RETURN_EMPRUNTE`) VALUES
(34, 22, '2023-06-22 19:51:24', '2023-06-08 20:13:01', '2023-07-07 19:51:24'),
(36, 25, '2023-06-22 20:26:30', '2023-06-22 20:26:41', '2023-07-07 20:26:30'),
(37, 27, '2023-06-22 20:30:42', '2023-06-22 20:31:14', '2023-07-07 20:30:42'),
(38, 28, '2023-06-23 00:59:46', '2023-06-23 01:08:52', '2023-07-08 00:59:46'),
(39, 29, '2023-06-23 01:09:25', '2023-06-23 01:09:37', '2023-07-08 01:09:25'),
(40, 30, '2023-06-23 01:10:57', '2023-06-23 01:11:35', '2023-07-08 01:10:57'),
(41, 31, '2023-06-23 01:12:40', '2023-06-23 01:12:54', '2023-07-08 01:12:40'),
(42, 32, '2023-06-23 01:31:36', '2023-06-23 01:31:51', '2023-07-08 01:31:36'),
(43, 33, '2023-06-23 01:32:59', '2023-06-23 01:33:04', '2023-07-08 01:32:59'),
(44, 34, '2023-06-23 01:33:54', '2023-06-23 01:33:58', '2023-07-08 01:33:54'),
(45, 35, '2023-06-23 01:34:13', '2023-06-23 01:34:19', '2023-07-08 01:34:13'),
(46, 43, '2023-06-23 12:31:55', NULL, '2023-07-08 12:31:55');

-- --------------------------------------------------------

--
-- Table structure for table `etagere`
--

CREATE TABLE `etagere` (
  `ID_ETAGERE` int(11) NOT NULL,
  `NBRRAYON` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `etagere`
--

INSERT INTO `etagere` (`ID_ETAGERE`, `NBRRAYON`) VALUES
(1, 5),
(2, 5),
(3, 5),
(4, 5);

-- --------------------------------------------------------

--
-- Table structure for table `etudier`
--

CREATE TABLE `etudier` (
  `ID_GROUPE` int(11) NOT NULL,
  `ID_PERSONNE` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `etudier`
--

INSERT INTO `etudier` (`ID_GROUPE`, `ID_PERSONNE`) VALUES
(3, 1),
(3, 2),
(3, 3);

-- --------------------------------------------------------

--
-- Table structure for table `favorie`
--

CREATE TABLE `favorie` (
  `ID_PERSONNE` int(11) NOT NULL,
  `ID_LIVRE` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `favorie`
--

INSERT INTO `favorie` (`ID_PERSONNE`, `ID_LIVRE`) VALUES
(2, 6);

-- --------------------------------------------------------

--
-- Table structure for table `filiere`
--

CREATE TABLE `filiere` (
  `ID_FILIERE` int(11) NOT NULL,
  `LIBELLEFILIERE` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `filiere`
--

INSERT INTO `filiere` (`ID_FILIERE`, `LIBELLEFILIERE`) VALUES
(1, 'GI'),
(2, 'IG'),
(3, 'GSI'),
(4, 'CPI');

-- --------------------------------------------------------

--
-- Table structure for table `groupe`
--

CREATE TABLE `groupe` (
  `ID_GROUPE` int(11) NOT NULL,
  `ID_NIVEAU` int(11) NOT NULL,
  `LIBELLE_GROUPE` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `groupe`
--

INSERT INTO `groupe` (`ID_GROUPE`, `ID_NIVEAU`, `LIBELLE_GROUPE`) VALUES
(1, 1, 'GI3-A'),
(2, 1, 'GI3-B'),
(3, 1, 'GI3-C'),
(4, 1, 'GI3-D');

-- --------------------------------------------------------

--
-- Table structure for table `lange`
--

CREATE TABLE `lange` (
  `ID_LANGUE` int(11) NOT NULL,
  `LIBELLE_LANGUE` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `lange`
--

INSERT INTO `lange` (`ID_LANGUE`, `LIBELLE_LANGUE`) VALUES
(1, 'arabic'),
(2, 'anglais'),
(3, 'french');

-- --------------------------------------------------------

--
-- Table structure for table `livre`
--

CREATE TABLE `livre` (
  `ID_LIVRE` int(11) NOT NULL,
  `ID_RAYON` int(11) DEFAULT NULL,
  `ID_LANGUE` int(11) NOT NULL,
  `ID_CATEGORIE` int(11) DEFAULT NULL,
  `TITRE` longtext NOT NULL,
  `ISBN` longtext NOT NULL,
  `DESCRIPTION` text NOT NULL,
  `ANNEEPUBLICATION` date NOT NULL,
  `NOMBREPAGE` int(11) NOT NULL,
  `PRIX` float NOT NULL,
  `COUVERTURE` longtext NOT NULL,
  `COUVERTURE_MIN` longtext NOT NULL,
  `QUANTITEREEL` int(11) NOT NULL,
  `QUANTITESTOCK` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `livre`
--

INSERT INTO `livre` (`ID_LIVRE`, `ID_RAYON`, `ID_LANGUE`, `ID_CATEGORIE`, `TITRE`, `ISBN`, `DESCRIPTION`, `ANNEEPUBLICATION`, `NOMBREPAGE`, `PRIX`, `COUVERTURE`, `COUVERTURE_MIN`, `QUANTITEREEL`, `QUANTITESTOCK`) VALUES
(1, 1, 2, 3, 'AMORALMAN: A True Story and Other Lies', 'sahdv65263vasb', 'Derek DelGaudio believed he was a decent, honest man. But when irrefutable evidence to the contrary is found in an old journal, his memories are reawakened and Derek is forced to confront--and try to understand--his role in a significant act of deception from his past.\n\nUsing his youthful notebook entries as a road map, Derek embarks on a soulful, often funny, sometimes dark journey, retracing the path that led him to a world populated by charlatans, card cheats, and con artists. As stories are peeled away and artifices are revealed, Derek examines the mystery behind his father\'s vanishing act, the secret he inherited from his mother, the obsession he developed with sleight-of-hand that shaped his future, and the affinity he felt for the professional swindlers who taught him how to deceive others. And once he finds himself working as a crooked dealer in a big-money Hollywood card game, Derek begins to question his own sense of morality, and discovers that even a master of deception can find himself trapped inside an illusion.', '2000-01-01', 108, 140, 'images/book_cover/A1cJRv42EXL.jpg', 'images/book_cover/wishlist_image/A1cJRv42EXL.jpg', 0, 0),
(2, NULL, 2, 1, 'THREE NOVELS YURI HERRERA', '1234FGF6', 'The Mexico we hear of in the news―the drug cartels, migration and senseless violence―is rich soil for Herrera’s moving stories of people who live in this reality but also live in the timeless realm of myth, epic and fairy tale, such as the singer Lobo in Kingdom Cons who loves the drug lord’s own daughter, Makina who crosses borders to find her brother in Signs Preceding the End of the World, and the Redeemer, a hard-boiled hero looking to broker peace between feuding families during a pandemic in The Transmigration of Bodies.', '2000-01-01', 23, 26, 'images/book_cover/61gS6X0fVL.jpg', 'images/book_cover/wishlist_image/61gS6X0fVL.jpg', 0, 0),
(3, NULL, 2, 1, 'THIS CLOSE TO OKEY', '256rey26', 'From the award-winning Southern writer who Roxane Gay calls \"a consummate storyteller\" comes a cathartic novel about the life-changing weekend shared between two strangers: a therapist and the man she prevents from ending his life.', '2015-06-10', 160, 400, 'images/book_cover/61SIocGgweS.jpg\r\n', 'images/book_cover/wishlist_image/61SIocGgweS.jpg\r\n', 4, 2),
(4, NULL, 2, 1, 'EDGE CASE', '1524dfsqgv', 'After another taxing day as the sole female employee at her New York City tech startup, Edwina comes home to find that her husband, Marlin, has packed up a suitcase and left. The only question now is why. Did he give up on their increasingly hopeless quest to secure their green cards and decide to return to Malaysia? Was it the death of his father that sent him into a tailspin? Or has his strange, sudden change in personality finally made Marlin and Edwina strangers to each other?\r\n\r\nAs Edwina searches the city for traces of her husband, she simultaneously sifts through memories of their relationship, hoping to discover the moment when something went wrong. All the while, a coworker is making increasingly uncomfortable advances toward her. And she can’t hide the truth about Marlin’s disappearance from her overbearing, eccentric mother for much longer. Soon Edwina will have to decide how much she is willing to sacrifice in order to stay in her marriage and in America.\r\n\r\nPoignant and darkly funny, Edge Case is a searing meditation on intimacy, estrangement, and the fractured nature of identity. In this moving debut, YZ Chin explores the imperfect yet enduring relationships we hold to country and family.', '2013-06-28', 240, 600, 'images/book_cover/71DBo02BnL.jpg\r\n', 'images/book_cover/wishlist_image/71DBo02BnL.jpg\r\n', 1, 1),
(5, NULL, 1, 1, 'SKINSHIP', '2635217bshdv', 'A long-married couple is forced to confront their friend\'s painful past when a church revival comes to a nearby town ... A woman in an arranged marriage struggles to connect with the son she hid from her husband for years ... A well-meaning sister unwittingly reunites an abuser with his victims.\r\n \r\nThrough an indelible array of lives, Yoon Choi explores where first and second generations either clash or find common ground, where meaning falls in the cracks between languages, where relationships bend under the weight of tenderness and disappointment, where displacement turns to heartbreak.', '2017-06-13', 77, 350, 'images/book_cover/71eQSNv5DL.jpg', 'images/book_cover/wishlist_image/71eQSNv5DL.jpg', 3, 1),
(6, NULL, 2, 1, 'Revival Season: A Novel', 'jhsab51vxsb', 'Every summer, fifteen-year-old Miriam Horton and her family pack themselves tight in their old minivan and travel through small southern towns for revival season: the time when Miriam’s father—one of the South’s most famous preachers—holds massive healing services for people desperate to be cured of ailments and disease. But, this summer, the revival season doesn’t go as planned, and after one service in which Reverend Horton’s healing powers are tested like never before, Miriam witnesses a shocking act of violence that shakes her belief in her father—and her faith.\r\n\r\nWhen the Hortons return home, Miriam’s confusion only grows as she discovers she might have the power to heal—even though her father and the church have always made it clear that such power is denied to women. Over the course of the following year, Miriam must decide between her faith, her family, and her newfound power that might be able to save others, but if discovered by her father, could destroy Miriam.', '2022-06-05', 160, 200, 'images/book_cover/71kXZFThXQS-678x1024.jpg', 'images/book_cover/wishlist_image/71kXZFThXQS-678x1024.jpg', 2, 2),
(7, NULL, 2, 1, 'HARROW', '2365217h23', 'Khristen is a teenager who,her mother believes, was marked by greatness as a baby when she died for a moment and then came back to life. After Khristen’s failing boarding school for gifted teens closes its doors, and she finds that her mother has disappeared, she ranges across the dead landscape and washes up at a “resort” on the shores of a mysterious, putrid lake the elderly residents there call “Big Girl.”\r\n \r\nIn a rotting honeycomb of rooms, these old ones plot actions to punish corporations and people they consider culpable in the destruction of the final scraps of nature’s beauty. What will Khristen and Jeffrey, the precocious ten-year-old boy she meets there, learn from this “gabby seditious lot, in the worst of health but with kamikaze hearts, an army of the aged and ill, determined to refresh, through crackpot violence, a plundered earth”?', '2019-06-11', 240, 250, 'images/book_cover/71XSZd8kBXL-693x1024.jpg', 'images/book_cover/wishlist_image/71XSZd8kBXL-693x1024.jpg', 1, 1),
(8, 3, 2, 2, 'Great Circle', '16526fsbxn', 'After being rescued as infants from a sinking ocean liner in 1914, Marian and Jamie Graves are raised by their dissolute uncle in Missoula, Montana. There—after encountering a pair of barnstorming pilots passing through town in beat-up biplanes—Marian commences her lifelong love affair with flight. At fourteen she drops out of school and finds an unexpected and dangerous patron in a wealthy bootlegger who provides a plane and subsidizes her lessons, an arrangement that will haunt her for the rest of her life, even as it allows her to fulfill her destiny: circumnavigating the globe by flying over the North and South Poles.\n\nA century later, Hadley Baxter is cast to play Marian in a film that centers on Marian\'s disappearance in Antarctica. Vibrant, canny, disgusted with the claustrophobia of Hollywood, Hadley is eager to redefine herself after a romantic film franchise has imprisoned her in the grip of cult celebrity. Her immersion into the character of Marian unfolds, thrillingly, alongside Marian\'s own story, as the two women\'s fates—and their hunger for self-determination in vastly different geographies and times—collide. Epic and emotional, meticulously researched and gloriously told, Great Circle is a monumental work of art, and a tremendous leap forward for the prodigiously gifted Maggie Shipstea', '2000-01-01', 140, 370, 'images/book_cover/91cryOAtAxL-674x1024.jpg', 'images/book_cover/wishlist_image/91cryOAtAxL-674x1024.jpg', 0, 0),
(9, NULL, 2, 3, 'AMORALMAN: A True Story and Other Lies', 'sahdv65263vasb', 'Derek DelGaudio believed he was a decent, honest man. But when irrefutable evidence to the contrary is found in an old journal, his memories are reawakened and Derek is forced to confront--and try to understand--his role in a significant act of deception from his past.\r\n\r\nUsing his youthful notebook entries as a road map, Derek embarks on a soulful, often funny, sometimes dark journey, retracing the path that led him to a world populated by charlatans, card cheats, and con artists. As stories are peeled away and artifices are revealed, Derek examines the mystery behind his father\'s vanishing act, the secret he inherited from his mother, the obsession he developed with sleight-of-hand that shaped his future, and the affinity he felt for the professional swindlers who taught him how to deceive others. And once he finds himself working as a crooked dealer in a big-money Hollywood card game, Derek begins to question his own sense of morality, and discovers that even a master of deception can find himself trapped inside an illusion.', '2023-06-14', 108, 140, 'images/book_cover/A1cJRv42EXL.jpg', 'images/book_cover/wishlist_image/A1cJRv42EXL.jpg', 2, 2);

-- --------------------------------------------------------

--
-- Table structure for table `niveau`
--

CREATE TABLE `niveau` (
  `ID_NIVEAU` int(11) NOT NULL,
  `ID_FILIERE` int(11) NOT NULL,
  `LIBELLE_NIVEAU` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `niveau`
--

INSERT INTO `niveau` (`ID_NIVEAU`, `ID_FILIERE`, `LIBELLE_NIVEAU`) VALUES
(1, 1, 'GI3'),
(2, 1, 'GI4'),
(3, 1, 'GI5'),
(4, 2, 'IG3'),
(5, 2, 'IG4'),
(6, 2, 'IG5'),
(7, 3, 'GSI3'),
(8, 3, 'GSI4'),
(9, 3, 'GSI5'),
(10, 4, 'CPI1'),
(11, 4, 'CPI2');

-- --------------------------------------------------------

--
-- Table structure for table `personne`
--

CREATE TABLE `personne` (
  `ID_PERSONNE` int(11) NOT NULL,
  `ID_statue` int(11) NOT NULL,
  `NOM` varchar(40) NOT NULL,
  `PRENOM` varchar(40) NOT NULL,
  `EMAIL` varchar(65) NOT NULL,
  `PASSWORD` varchar(200) NOT NULL,
  `NUMEROTEL` longtext NOT NULL,
  `CIN` longtext NOT NULL,
  `DATENAISSANCE` date NOT NULL,
  `AGE` int(11) NOT NULL,
  `archive` bit(1) NOT NULL DEFAULT b'0',
  `newsletter` bit(1) NOT NULL DEFAULT b'0'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `personne`
--

INSERT INTO `personne` (`ID_PERSONNE`, `ID_statue`, `NOM`, `PRENOM`, `EMAIL`, `PASSWORD`, `NUMEROTEL`, `CIN`, `DATENAISSANCE`, `AGE`, `archive`, `newsletter`) VALUES
(1, 1, 'elbasri', 'ahmed', 'ahmed123elbasri@gmail.com', '32aa2fd87338e241978c48ab319641bc', '0502134325', 'f1123', '2002-04-22', 21, b'0', b'1'),
(2, 2, 'boussaidi', 'ayoub', 'ayoub@gmail.com', '92fe2eb6d27f88a0e6af7e1632abaa39', '4124232412', 'f123456', '1999-05-05', 24, b'0', b'0'),
(3, 3, 'mokhliss', 'karim', 'karim@gmail.com', '86daa7cd600c9817465d4fde34446278', '0612345678', 'f543', '2001-06-13', 22, b'0', b'0'),
(4, 1, 'abdo', 'abdo', 'abdo@gmail.com', '461e13feea4fa0f80b93849dda5bf299', '0623124234', 'f35436', '1998-06-11', 24, b'0', b'0'),
(5, 2, 'boussaidi', 'ayoub', 'ayoubbale@hotmail.com', 'd41d8cd98f00b204e9800998ecf8427e', '07232323', 'cin', '2000-01-01', 23, b'1', b'0');

-- --------------------------------------------------------

--
-- Table structure for table `rayon`
--

CREATE TABLE `rayon` (
  `ID_RAYON` int(11) NOT NULL,
  `ID_ETAGER` int(14) NOT NULL,
  `CAPACITERAYON` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `rayon`
--

INSERT INTO `rayon` (`ID_RAYON`, `ID_ETAGER`, `CAPACITERAYON`) VALUES
(1, 1, 10),
(2, 1, 10),
(3, 1, 10),
(4, 1, 10),
(5, 1, 10),
(6, 2, 10),
(7, 2, 10),
(8, 2, 10),
(9, 2, 10),
(10, 2, 10),
(11, 3, 10),
(12, 3, 10),
(13, 3, 10),
(14, 3, 10),
(15, 3, 10),
(16, 4, 10),
(17, 4, 10),
(18, 4, 10),
(19, 4, 10),
(20, 4, 10);

-- --------------------------------------------------------

--
-- Table structure for table `rediger`
--

CREATE TABLE `rediger` (
  `ID_LIVRE` int(11) NOT NULL,
  `ID_AUTEUR` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `rediger`
--

INSERT INTO `rediger` (`ID_LIVRE`, `ID_AUTEUR`) VALUES
(1, 4),
(2, 5),
(3, 5),
(4, 6),
(5, 5),
(6, 6),
(7, 4),
(8, 4),
(9, 4);

-- --------------------------------------------------------

--
-- Table structure for table `reserverlivre`
--

CREATE TABLE `reserverlivre` (
  `ID_RESERVATION` int(11) NOT NULL,
  `ID_PERSONNE` int(11) NOT NULL,
  `ID_LIVRE` int(11) NOT NULL,
  `DATERESERVATION` datetime NOT NULL,
  `ETAT` text NOT NULL DEFAULT 'pending',
  `archive` bit(1) NOT NULL DEFAULT b'0',
  `DATE_END_RESERVATION` datetime DEFAULT (`DATERESERVATION` + interval 48 hour)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `reserverlivre`
--

INSERT INTO `reserverlivre` (`ID_RESERVATION`, `ID_PERSONNE`, `ID_LIVRE`, `DATERESERVATION`, `ETAT`, `archive`, `DATE_END_RESERVATION`) VALUES
(19, 1, 1, '2023-06-22 20:38:02', 'canceled', b'1', '2023-06-24 20:38:02'),
(20, 1, 1, '2023-06-22 20:38:23', 'canceled', b'1', '2023-06-24 20:38:23'),
(21, 1, 1, '2023-06-22 20:38:44', 'canceled', b'1', '2023-06-24 20:38:44'),
(22, 1, 1, '2023-06-22 20:50:52', 'canceled', b'1', '2023-06-24 20:50:52'),
(23, 1, 1, '2023-06-22 20:51:48', 'canceled', b'1', '2023-06-24 20:51:48'),
(24, 1, 1, '2023-06-22 21:23:58', 'canceled', b'1', '2023-06-24 21:23:58'),
(25, 1, 3, '2023-06-22 21:25:42', 'approved', b'1', '2023-06-24 21:25:42'),
(26, 1, 8, '2023-06-22 21:27:25', 'canceled', b'1', '2023-06-24 21:27:25'),
(27, 1, 2, '2023-06-22 21:30:09', 'canceled', b'1', '2023-06-24 21:30:09'),
(28, 1, 1, '2023-06-22 21:31:23', 'canceled', b'1', '2023-06-24 21:31:23'),
(29, 1, 2, '2023-06-23 02:09:17', 'canceled', b'1', '2023-06-25 02:09:17'),
(30, 1, 4, '2023-06-23 02:10:40', 'approved', b'1', '2023-06-25 02:10:40'),
(31, 3, 8, '2023-06-23 02:12:21', 'approved', b'1', '2023-06-25 02:12:21'),
(32, 3, 1, '2023-06-23 02:31:30', 'canceled', b'1', '2023-06-25 02:31:30'),
(33, 4, 8, '2023-06-23 02:32:46', 'approved', b'1', '2023-06-25 02:32:46'),
(34, 2, 3, '2023-06-23 02:33:48', 'approved', b'1', '2023-06-25 02:33:48'),
(35, 2, 9, '2023-06-23 02:34:06', 'approved', b'1', '2023-06-25 02:34:06'),
(36, 2, 1, '2023-06-23 02:39:37', 'canceled', b'1', '2023-06-25 02:39:37'),
(37, 2, 2, '2023-06-23 02:43:13', 'canceled', b'1', '2023-06-25 02:43:13'),
(38, 1, 1, '2023-06-23 02:49:49', 'canceled', b'1', '2023-06-25 02:49:49'),
(39, 1, 2, '2023-06-23 03:20:39', 'canceled', b'1', '2023-06-25 03:20:39'),
(40, 2, 5, '2023-06-23 09:22:31', 'canceled', b'1', '2023-06-25 09:22:31'),
(41, 2, 2, '2023-06-23 10:02:16', 'canceled', b'1', '2023-06-25 10:02:16'),
(42, 2, 5, '2023-06-23 12:20:36', 'pending', b'0', '2023-06-25 12:20:36'),
(43, 1, 2, '2023-06-23 13:31:36', 'approved', b'1', '2023-06-25 13:31:36');

-- --------------------------------------------------------

--
-- Table structure for table `statut`
--

CREATE TABLE `statut` (
  `ID` int(11) NOT NULL,
  `LIBELLE` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `statut`
--

INSERT INTO `statut` (`ID`, `LIBELLE`) VALUES
(1, 'admin'),
(2, 'rsb'),
(3, 'etudiant');

-- --------------------------------------------------------

--
-- Table structure for table `traduite`
--

CREATE TABLE `traduite` (
  `ID_LIVRE` int(11) NOT NULL,
  `ID_LANGUE` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `appartientt`
--
ALTER TABLE `appartientt`
  ADD PRIMARY KEY (`ID_RAYON`,`ID_ETAGERE`),
  ADD KEY `FK_APPARTIENTT` (`ID_ETAGERE`);

--
-- Indexes for table `auteur`
--
ALTER TABLE `auteur`
  ADD PRIMARY KEY (`ID_AUTEUR`);

--
-- Indexes for table `categorie`
--
ALTER TABLE `categorie`
  ADD PRIMARY KEY (`ID_CATEGORIE`);

--
-- Indexes for table `empruntlivre`
--
ALTER TABLE `empruntlivre`
  ADD PRIMARY KEY (`ID_EMPRUNTE`),
  ADD KEY `FK_IDRESERVATION` (`ID_RESERVATION`);

--
-- Indexes for table `etagere`
--
ALTER TABLE `etagere`
  ADD PRIMARY KEY (`ID_ETAGERE`);

--
-- Indexes for table `etudier`
--
ALTER TABLE `etudier`
  ADD PRIMARY KEY (`ID_GROUPE`,`ID_PERSONNE`),
  ADD KEY `FK_ETUDIER` (`ID_PERSONNE`);

--
-- Indexes for table `favorie`
--
ALTER TABLE `favorie`
  ADD PRIMARY KEY (`ID_PERSONNE`,`ID_LIVRE`),
  ADD KEY `FK_FAVORIE` (`ID_LIVRE`);

--
-- Indexes for table `filiere`
--
ALTER TABLE `filiere`
  ADD PRIMARY KEY (`ID_FILIERE`);

--
-- Indexes for table `groupe`
--
ALTER TABLE `groupe`
  ADD PRIMARY KEY (`ID_GROUPE`),
  ADD KEY `FK_COMPOSER` (`ID_NIVEAU`);

--
-- Indexes for table `lange`
--
ALTER TABLE `lange`
  ADD PRIMARY KEY (`ID_LANGUE`);

--
-- Indexes for table `livre`
--
ALTER TABLE `livre`
  ADD PRIMARY KEY (`ID_LIVRE`),
  ADD KEY `FK_APPARTIENT` (`ID_RAYON`),
  ADD KEY `FK_DEPEND` (`ID_CATEGORIE`),
  ADD KEY `FK_ORIGINALE` (`ID_LANGUE`);

--
-- Indexes for table `niveau`
--
ALTER TABLE `niveau`
  ADD PRIMARY KEY (`ID_NIVEAU`),
  ADD KEY `FK_CONTIENT` (`ID_FILIERE`);

--
-- Indexes for table `personne`
--
ALTER TABLE `personne`
  ADD PRIMARY KEY (`ID_PERSONNE`),
  ADD UNIQUE KEY `EMAIL` (`EMAIL`),
  ADD KEY `FK_EST_` (`ID_statue`);

--
-- Indexes for table `rayon`
--
ALTER TABLE `rayon`
  ADD PRIMARY KEY (`ID_RAYON`),
  ADD KEY `fk_idetager` (`ID_ETAGER`);

--
-- Indexes for table `rediger`
--
ALTER TABLE `rediger`
  ADD PRIMARY KEY (`ID_LIVRE`,`ID_AUTEUR`),
  ADD KEY `FK_REDIGER` (`ID_AUTEUR`);

--
-- Indexes for table `reserverlivre`
--
ALTER TABLE `reserverlivre`
  ADD PRIMARY KEY (`ID_RESERVATION`),
  ADD KEY `fk_idpersonne` (`ID_PERSONNE`),
  ADD KEY `fk_idlivre` (`ID_LIVRE`);

--
-- Indexes for table `statut`
--
ALTER TABLE `statut`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `traduite`
--
ALTER TABLE `traduite`
  ADD PRIMARY KEY (`ID_LIVRE`,`ID_LANGUE`),
  ADD KEY `FK_TRADUITE` (`ID_LANGUE`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `empruntlivre`
--
ALTER TABLE `empruntlivre`
  MODIFY `ID_EMPRUNTE` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;

--
-- AUTO_INCREMENT for table `reserverlivre`
--
ALTER TABLE `reserverlivre`
  MODIFY `ID_RESERVATION` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=44;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `appartientt`
--
ALTER TABLE `appartientt`
  ADD CONSTRAINT `FK_APPARTIENTT` FOREIGN KEY (`ID_ETAGERE`) REFERENCES `etagere` (`ID_ETAGERE`),
  ADD CONSTRAINT `FK_APPARTIENTT2` FOREIGN KEY (`ID_RAYON`) REFERENCES `rayon` (`ID_RAYON`);

--
-- Constraints for table `empruntlivre`
--
ALTER TABLE `empruntlivre`
  ADD CONSTRAINT `FK_IDRESERVATION` FOREIGN KEY (`ID_RESERVATION`) REFERENCES `reserverlivre` (`ID_RESERVATION`);

--
-- Constraints for table `etudier`
--
ALTER TABLE `etudier`
  ADD CONSTRAINT `FK_ETUDIER` FOREIGN KEY (`ID_PERSONNE`) REFERENCES `personne` (`ID_PERSONNE`),
  ADD CONSTRAINT `FK_ETUDIER2` FOREIGN KEY (`ID_GROUPE`) REFERENCES `groupe` (`ID_GROUPE`);

--
-- Constraints for table `favorie`
--
ALTER TABLE `favorie`
  ADD CONSTRAINT `FK_FAVORIE` FOREIGN KEY (`ID_LIVRE`) REFERENCES `livre` (`ID_LIVRE`),
  ADD CONSTRAINT `FK_FAVORIE2` FOREIGN KEY (`ID_PERSONNE`) REFERENCES `personne` (`ID_PERSONNE`);

--
-- Constraints for table `groupe`
--
ALTER TABLE `groupe`
  ADD CONSTRAINT `FK_COMPOSER` FOREIGN KEY (`ID_NIVEAU`) REFERENCES `niveau` (`ID_NIVEAU`);

--
-- Constraints for table `livre`
--
ALTER TABLE `livre`
  ADD CONSTRAINT `FK_APPARTIENT` FOREIGN KEY (`ID_RAYON`) REFERENCES `rayon` (`ID_RAYON`),
  ADD CONSTRAINT `FK_DEPEND` FOREIGN KEY (`ID_CATEGORIE`) REFERENCES `categorie` (`ID_CATEGORIE`),
  ADD CONSTRAINT `FK_ORIGINALE` FOREIGN KEY (`ID_LANGUE`) REFERENCES `lange` (`ID_LANGUE`);

--
-- Constraints for table `niveau`
--
ALTER TABLE `niveau`
  ADD CONSTRAINT `FK_CONTIENT` FOREIGN KEY (`ID_FILIERE`) REFERENCES `filiere` (`ID_FILIERE`);

--
-- Constraints for table `personne`
--
ALTER TABLE `personne`
  ADD CONSTRAINT `FK_EST_` FOREIGN KEY (`ID_statue`) REFERENCES `statut` (`ID`);

--
-- Constraints for table `rayon`
--
ALTER TABLE `rayon`
  ADD CONSTRAINT `fk_idetager` FOREIGN KEY (`ID_ETAGER`) REFERENCES `etagere` (`ID_ETAGERE`);

--
-- Constraints for table `rediger`
--
ALTER TABLE `rediger`
  ADD CONSTRAINT `FK_REDIGER` FOREIGN KEY (`ID_AUTEUR`) REFERENCES `auteur` (`ID_AUTEUR`),
  ADD CONSTRAINT `FK_REDIGER2` FOREIGN KEY (`ID_LIVRE`) REFERENCES `livre` (`ID_LIVRE`);

--
-- Constraints for table `reserverlivre`
--
ALTER TABLE `reserverlivre`
  ADD CONSTRAINT `fk_idlivre` FOREIGN KEY (`ID_LIVRE`) REFERENCES `livre` (`ID_LIVRE`),
  ADD CONSTRAINT `fk_idpersonne` FOREIGN KEY (`ID_PERSONNE`) REFERENCES `personne` (`ID_PERSONNE`);

--
-- Constraints for table `traduite`
--
ALTER TABLE `traduite`
  ADD CONSTRAINT `FK_TRADUITE` FOREIGN KEY (`ID_LANGUE`) REFERENCES `lange` (`ID_LANGUE`),
  ADD CONSTRAINT `FK_TRADUITE2` FOREIGN KEY (`ID_LIVRE`) REFERENCES `livre` (`ID_LIVRE`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
