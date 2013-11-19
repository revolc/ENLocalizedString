### Introduction

**What's l10n?**

Language localisation[nb 1] is the process of adapting a product that has been previously translated into different languages to a specific country or region (from Latin locus (place) and the English term locale, "a place where something happens or is set"). You can go to this [wikipedia page](http://en.wikipedia.org/wiki/L10n) for more information.

**L10n in Cocos2d-x**

The l10n process in iOS or Android is easy enough. But by the time of writting, there seem no official way/class to play. So I wrote this lib, hope that may save your work.

### Dependency

There's nothing special to #include, make this lib as light-weight as possible.

You just need to cocos2d-x lib setup, nothing else required.

### Configuration

This class is a singleton object that load "Localized_xx.plist" file into a CCDictionary, so that we can look up localized string more quickly.

The "Localized_xx.plist" is the file storing the localized strings. The "xx" subfix can be "zh", "en", "ru", "es", etc., as defined by ccLanguageType:

	typedef enum LanguageType
	{
	    kLanguageEnglish = 0,
	    kLanguageChinese,
	    kLanguageFrench,
	    kLanguageItalian,
	    kLanguageGerman,
	    kLanguageSpanish,
	    kLanguageRussian,
	    kLanguageKorean,
	    kLanguageJapanese,
	    kLanguageHungarian,
	    kLanguagePortuguese,
	    kLanguageArabic
	} ccLanguageType;

The way "Localized_xx.plist" comes from in 2 favor:

1. The default behavior is defined as `kENLocalizedFileLocationTypePackage`. If you just put files in the `Resources/` folder, then nothing else need to configure. It will load the file by the locale setting of the device and the above fule.

2. However, it's sometimes more useful if the l10n file can be download into app sandbox, so that we can easily change the wording without repackaging the game. To have this benefit, you need to `setLocalizedFileLocationType` to `kENLocalizedFileLocationTypeSandbox` AND PLEASE REMEMBER TO `setLocalizedFolderPath` to the folder containing the "Localiezd_xx.plist" file. Otherwise the class will crash when trying to retrieve localized strings.


### Usage

To this step, you can get strings in Localized_xx.plist using `getLocalizedString`:

	ENLocalizationManager::sharedManager()->getLocalizedString(key)

However, this may seem verbose, with ENLocalizationUtils namespace included in your code, you can just type:

	ENLocalizedString(key)

to retrieve localized string.
