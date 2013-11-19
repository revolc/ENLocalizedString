//
//  ENLocalizationManager.h
//  NewDaka
//
//  Created by revolc on 13-11-19.
//
//

#ifndef __NewDaka__ENLocalizationManager__
#define __NewDaka__ENLocalizationManager__

#include "cocos2d.h"
USING_NS_CC;
#include <iostream>

enum ENLocalizedFileLocationType {
    kENLocalizedFileLocationTypePackage = 0,
    kENLocalizedFileLocationTypeSandbox = 1
    };

class ENLocalizationManager: public CCObject {
    
public:
    ~ENLocalizationManager();
    ENLocalizationManager();
    
    static ENLocalizationManager *sharedManager();

    /* The Localized_xx.plist can be in application package or in the sandbox.
     * kENLocalizedFileLocationTypePackage: 
     *  The class will look for l10n file in the package, namely Resources/
     *  folder of the project;
     * kENLocalizedFileLocationTypeSandbox:
     *  The l10n file can be download from web into the application sandbox,
     *  making it easier to update content of l10n file without repackaging app.
     */
    void setLocalizedFileLocationType(ENLocalizedFileLocationType type);
    
    /* Set the folder path
     * specify where to look up Localized_xx.plist,
     * where xx can be zh, en, ru, es, etc., as defined by ccLanguageType
     * MUST set the folder if kENLocalizedFileLocationTypeSandbox is applied;
     * CAN leave if alone if kENLocalizedFileLocationTypePackage
     */
    void setLocalizedFolderPath(std::string folderPath);

    /* Get the localized string by key
     * We also provide ENLocalizationUtils name space so that
     * instead of writting 
     *   ENLocalizationManager::sharedManager()->getLocalizedString(key)
     * to get string, just use
     *   ENLocalizationUtils::ENLocalizedString(key)
     * to save the type.
     * If you include the name space in your code like this:
     *   using namespace ENLocalizationUtils;
     * You can even save more key stroke like this:
     *   ENLocalizedString(key)   
     */
    const char *getLocalizedString(std::string key);
    
private:
    
    // specifies the l10n file lookup policy
    ENLocalizedFileLocationType m_nLocationType;

    // the key/value map of l10n content
    CCDictionary *m_pLocalizedStringMap;
    
    // private helper function to load the l10n file into mem.
    void loadLocalizedPlistFile();
    
    // private helper function to unload the l10n file
    void unloadLocalizedPlistFile();
    
    // determine which l10n file to load during app runtime
    std::string localizedFileName();

    // the folder to look up l10n file
    std::string m_sFolderPath;
    
};

namespace ENLocalizationUtils {
    const char *ENLocalizedString(std::string key);
}

#endif /* defined(__NewDaka__ENLocalizationManager__) */
