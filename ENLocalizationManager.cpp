//
//  ENLocalizationManager.cpp
//  NewDaka
//
//  Created by revolc on 13-11-19.
//
//

#include "ENLocalizationManager.h"

#include "CCApplication.h"

static ENLocalizationManager *s_sharedManager = NULL;

ENLocalizationManager::~ENLocalizationManager()
{
    CC_SAFE_RELEASE(m_pLocalizedStringMap);
    
}

ENLocalizationManager::ENLocalizationManager()
{
    m_pLocalizedStringMap = NULL;
    this->setLocalizedFileLocationType(kENLocalizedFileLocationTypePackage);
}

ENLocalizationManager *ENLocalizationManager::sharedManager()
{
    if (!s_sharedManager) {
        s_sharedManager = new ENLocalizationManager();
    }
    return s_sharedManager;
}

void ENLocalizationManager::loadLocalizedPlistFile()
{
    std::string filePath = localizedFileName();
    
    if (m_nLocationType == kENLocalizedFileLocationTypeSandbox) {
        filePath = m_sFolderPath + filePath;
    }
    
    m_pLocalizedStringMap = CCDictionary::createWithContentsOfFile(filePath.c_str());
    
    m_pLocalizedStringMap->retain();
}

void ENLocalizationManager::unloadLocalizedPlistFile()
{
    if (m_pLocalizedStringMap) {
        CC_SAFE_RELEASE_NULL(m_pLocalizedStringMap);
    }
}

void ENLocalizationManager::setLocalizedFileLocationType(ENLocalizedFileLocationType type)
{
    m_nLocationType = type;
    this->unloadLocalizedPlistFile();
}

void ENLocalizationManager::setLocalizedFolderPath(std::string folderPath)
{
    m_sFolderPath = folderPath;
    this->unloadLocalizedPlistFile();
}

std::string ENLocalizationManager::localizedFileName()
{    
    ccLanguageType curLanguage = CCApplication::sharedApplication()->getCurrentLanguage();
    
    std::string subfix = "en";
    switch (curLanguage) {
        case kLanguageEnglish:
            subfix = "en";
            break;
        case kLanguageChinese:
            subfix = "zh";
            break;
        case kLanguageFrench:
            subfix = "fr";
            break;
        case kLanguageItalian:
            subfix = "it";
            break;
        case kLanguageGerman:
            subfix = "de";
            break;
        case kLanguageSpanish:
            subfix = "es";
            break;
        case kLanguageRussian:
            subfix = "ru";
            break;
        case kLanguageKorean:
            subfix = "ko";
            break;
        case kLanguageJapanese:
            subfix = "ja";
            break;
        case kLanguageHungarian:
            subfix = "hu";
            break;
        case kLanguagePortuguese:
            subfix = "pt";
            break;
        case kLanguageArabic:
            subfix = "ar";
            break;
            
        default:
            break;
    }
    CCString *fileName = CCString::createWithFormat("Localized_%s.plist", subfix.c_str());
    
    return fileName->getCString();
}

const char *ENLocalizationManager::getLocalizedString(std::string key)
{
    if (NULL == m_pLocalizedStringMap) {
        loadLocalizedPlistFile();
    }
    
    CCString *localizedStr = (CCString*)m_pLocalizedStringMap->objectForKey(key);
    return localizedStr->getCString();
}

namespace ENLocalizationUtils {
    const char *ENLocalizedString(std::string key)
    {
        return ENLocalizationManager::sharedManager()->getLocalizedString(key);
    }
}
