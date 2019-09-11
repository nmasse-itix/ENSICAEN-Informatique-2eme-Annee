/*
 * #(@)ImageDisplayer.java                ENSICAEN                     2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

package mybeans;

import javax.swing.*;
import java.beans.*;

/**
 * Cette classe à été construite à l'aide de l'IDE netbeans, les variables 
 * membres, la méthode initComponents() et les autres méthodes privées sont 
 * auto-générés. Cette classe lie les beans développés dans ce TP au sein 
 * d'un interface graphique.
 *
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class ImageDisplayer extends JPanel {
    
    /**
     * Construit un nouveau composant.
     */
    public ImageDisplayer() {
        initComponents();
        
        // Enregistrement de l'écouteur
        this.ibImage.addImageChangedListener(this.lblImage);
    }
    
    /** This method is called from within the constructor to initialize 
     * the form.
     */
    // <editor-fold defaultstate="collapsed" desc=" Generated Code ">//GEN-BEGIN:initComponents
    private void initComponents() {
        itImage = new mybeans.ImageIterator();
        timer = new mybeans.TimerBean();
        btDebut = new javax.swing.JButton();
        btPrec = new javax.swing.JButton();
        btSuiv = new javax.swing.JButton();
        btFin = new javax.swing.JButton();
        lblImage = new mybeans.LabelBean();
        ibImage = new mybeans.ImageBean();
        sldDelai = new javax.swing.JSlider();
        lblDelai = new javax.swing.JLabel();
        lblValeur = new javax.swing.JLabel();
        chkBoucle = new javax.swing.JCheckBox();
        chkDiapo = new javax.swing.JCheckBox();

        itImage.setDirName("/usr/share/pixmaps");
        itImage.setLoop(chkBoucle.isSelected());
        itImage.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                itImagePropertyChange(evt);
            }
        });

        timer.setDiaporama(chkDiapo.isSelected());
        timer.setMain(new Runnable() {public void run() {itImage.next();}});
        timer.setTime(sldDelai.getValue());
        timer.addPropertyChangeListener(new java.beans.PropertyChangeListener() {
            public void propertyChange(java.beans.PropertyChangeEvent evt) {
                timerPropertyChange(evt);
            }
        });

        btDebut.setText("D\u00e9but");
        btDebut.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btDebutActionPerformed(evt);
            }
        });

        btPrec.setText("Pr\u00e9c\u00e9dent");
        btPrec.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btPrecActionPerformed(evt);
            }
        });

        btSuiv.setText("Suivant");
        btSuiv.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btSuivActionPerformed(evt);
            }
        });

        btFin.setText("Fin");
        btFin.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btFinActionPerformed(evt);
            }
        });

        lblImage.setBackground(new java.awt.Color(153, 153, 153));
        lblImage.setBorder(new javax.swing.border.LineBorder(new java.awt.Color(0, 0, 0), 1, true));
        lblImage.setText(" ");

        ibImage.setImageFileName("/usr/share/pixmaps/gaim.png");
        ibImage.addImageChangedListener(new mybeans.ImageChangedListener() {
            public void imageChanged(mybeans.ImageChangedEvent evt) {
                ibImageImageChanged(evt);
            }
        });

        sldDelai.setMaximum(60);
        sldDelai.setMinimum(3);
        sldDelai.setValue(15);
        sldDelai.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                sldDelaiStateChanged(evt);
            }
        });

        lblDelai.setText("D\u00e9lai entre les images");

        lblValeur.setText("15");

        chkBoucle.setText("Boucle");
        chkBoucle.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        chkBoucle.setMargin(new java.awt.Insets(0, 0, 0, 0));
        chkBoucle.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                chkBoucleStateChanged(evt);
            }
        });

        chkDiapo.setText("Diaporama");
        chkDiapo.setBorder(javax.swing.BorderFactory.createEmptyBorder(0, 0, 0, 0));
        chkDiapo.setMargin(new java.awt.Insets(0, 0, 0, 0));
        chkDiapo.addChangeListener(new javax.swing.event.ChangeListener() {
            public void stateChanged(javax.swing.event.ChangeEvent evt) {
                chkDiapoStateChanged(evt);
            }
        });

        org.jdesktop.layout.GroupLayout layout = new org.jdesktop.layout.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                .addContainerGap()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                        .add(chkBoucle)
                        .add(48, 48, 48)
                        .add(chkDiapo))
                    .add(org.jdesktop.layout.GroupLayout.TRAILING, layout.createSequentialGroup()
                        .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                            .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                                .add(lblDelai)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 375, Short.MAX_VALUE)
                                .add(lblValeur)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                                .add(sldDelai, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 345, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE))
                            .add(lblImage, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 887, Short.MAX_VALUE))
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED))
                    .add(org.jdesktop.layout.GroupLayout.TRAILING, layout.createSequentialGroup()
                        .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                            .add(ibImage, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, 887, Short.MAX_VALUE)
                            .add(org.jdesktop.layout.GroupLayout.TRAILING, layout.createSequentialGroup()
                                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                                    .add(btDebut)
                                    .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                                        .add(159, 159, 159)
                                        .add(btPrec)))
                                .add(83, 83, 83)
                                .add(btSuiv)
                                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED, 418, Short.MAX_VALUE)
                                .add(btFin)))
                        .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)))
                .add(658, 658, 658)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
            .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                .addContainerGap()
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createParallelGroup(org.jdesktop.layout.GroupLayout.TRAILING)
                        .add(btDebut)
                        .add(btFin))
                    .add(btPrec)
                    .add(btSuiv))
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(ibImage, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, 320, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(lblImage, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(org.jdesktop.layout.LayoutStyle.RELATED)
                .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                    .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                        .add(lblValeur)
                        .addContainerGap())
                    .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                        .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                            .add(sldDelai, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE, org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, org.jdesktop.layout.GroupLayout.PREFERRED_SIZE)
                            .addContainerGap())
                        .add(org.jdesktop.layout.GroupLayout.LEADING, layout.createSequentialGroup()
                            .add(lblDelai)
                            .add(7, 7, 7)
                            .add(layout.createParallelGroup(org.jdesktop.layout.GroupLayout.LEADING)
                                .add(chkBoucle)
                                .add(chkDiapo))
                            .addContainerGap(org.jdesktop.layout.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))))
        );
    }
    // </editor-fold>//GEN-END:initComponents

    private void chkDiapoStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_chkDiapoStateChanged
        timer.setDiaporama(chkDiapo.isSelected());
    }//GEN-LAST:event_chkDiapoStateChanged

    private void chkBoucleStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_chkBoucleStateChanged
        itImage.setLoop(chkBoucle.isSelected());
    }//GEN-LAST:event_chkBoucleStateChanged

    private void timerPropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_timerPropertyChange
        if (evt.getPropertyName().equals(TimerBean.PROP_TIME)) {
            lblValeur.setText(Integer.toString(timer.getTime()));
        }
    }//GEN-LAST:event_timerPropertyChange

    private void sldDelaiStateChanged(javax.swing.event.ChangeEvent evt) {//GEN-FIRST:event_sldDelaiStateChanged
        timer.setTime(sldDelai.getValue());
    }//GEN-LAST:event_sldDelaiStateChanged

    private void ibImageImageChanged(mybeans.ImageChangedEvent evt) {//GEN-FIRST:event_ibImageImageChanged
        
    }//GEN-LAST:event_ibImageImageChanged

    private void btSuivActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btSuivActionPerformed
        itImage.next();
    }//GEN-LAST:event_btSuivActionPerformed

    private void btPrecActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btPrecActionPerformed
        itImage.prev();
    }//GEN-LAST:event_btPrecActionPerformed

    private void itImagePropertyChange(java.beans.PropertyChangeEvent evt) {//GEN-FIRST:event_itImagePropertyChange
        if (evt.getPropertyName().equals(ImageIterator.PROP_CUR_IMAGE)) {
            String file = (String) evt.getNewValue();
            ibImage.setImageFileName(file);
        }
    }//GEN-LAST:event_itImagePropertyChange

    private void btFinActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btFinActionPerformed
        itImage.end();
    }//GEN-LAST:event_btFinActionPerformed

    private void btDebutActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btDebutActionPerformed
        itImage.start();
    }//GEN-LAST:event_btDebutActionPerformed
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btDebut;
    private javax.swing.JButton btFin;
    private javax.swing.JButton btPrec;
    private javax.swing.JButton btSuiv;
    private javax.swing.JCheckBox chkBoucle;
    private javax.swing.JCheckBox chkDiapo;
    private mybeans.ImageBean ibImage;
    private mybeans.ImageIterator itImage;
    private javax.swing.JLabel lblDelai;
    private mybeans.LabelBean lblImage;
    private javax.swing.JLabel lblValeur;
    private javax.swing.JSlider sldDelai;
    private mybeans.TimerBean timer;
    // End of variables declaration//GEN-END:variables
    
}
