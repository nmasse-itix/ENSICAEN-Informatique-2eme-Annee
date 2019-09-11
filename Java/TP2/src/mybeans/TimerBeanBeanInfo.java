/*
 * #(@)TimerBeanBeanInfo.java              ENSICAEN                  2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

package mybeans;

import java.awt.Image;
import java.beans.BeanDescriptor;
import java.beans.SimpleBeanInfo;
import java.beans.BeanInfo;
import java.beans.EventSetDescriptor;
import java.beans.MethodDescriptor;
import java.beans.PropertyDescriptor;

/**
 * Décrit le bean TimerBean.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class TimerBeanBeanInfo extends SimpleBeanInfo {
    private Image icon;
    
    /**
     * Creates a new instance of TimerBeanBeanInfo
     */
    public TimerBeanBeanInfo() {
        this.icon = loadImage("TimerBean.png");
    }

    public Image getIcon(int iconKind) {
        Image ret = null;
        
        switch (iconKind) {
            case ICON_COLOR_32x32:
                ret = this.icon;
                break;
            default:
                break;
        }
        
        return ret;
    }
    
}
